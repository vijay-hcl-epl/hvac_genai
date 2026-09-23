/**
 * @file system_init.c
 * @brief System Startup / Initialisation Software Unit – Implementation
 *
 * Traceability:
 *   SWE-REQ-020, SWE-REQ-021
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 *
 * Peripheral configuration:
 *   USART2 : 9600 baud, 8N1 (UART command input)
 *   ADC1   : Channel 1 (PA1), 12-bit, single conversion
 *   TIM2   : Channel 1 (PA0), PWM mode, 1 kHz
 *   GPIO   : PB0/PB1 (motor IN1/IN2), PD12 (power LED),
 *            PE2-PE6 (position LEDs)
 *
 * [SWE-REQ-020, SWE-REQ-015, SWE-REQ-016, SWE-REQ-017, SWE-REQ-018]
 */

#include "system_init.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "flap_control_logic.h"
#include "motor_driver.h"
#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---------- Peripheral handles (global, used by other units) ---------- */
/* [SWE-REQ-019, SWE-REQ-038] */

UART_HandleTypeDef huart2;
ADC_HandleTypeDef  hadc1;
TIM_HandleTypeDef  htim2;

/* ---------- Private: Clock configuration ---------- */

/**
 * @brief Configure the system clock for STM32F407.
 *        Uses HSI (16 MHz) as a simple default.
 *        [SWE-REQ-020]
 */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Configure HSI as system clock source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;
    (void)HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                     | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    (void)HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

/* ---------- Private: GPIO init ---------- */

/**
 * @brief Initialise GPIO pins for motor direction, power LED, and position LEDs.
 *        [SWE-REQ-016, SWE-REQ-018, SWE-REQ-020]
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Enable GPIO clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* Motor direction: PB0 (IN1), PB1 (IN2) – Push-pull output */
    GPIO_InitStruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);

    /* Power LED: PD12 – Push-pull output */
    GPIO_InitStruct.Pin   = GPIO_PIN_12;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    /* Position LEDs: PE2..PE6 – Push-pull output */
    GPIO_InitStruct.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                          | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                            | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
}

/* ---------- Private: UART init ---------- */

/**
 * @brief Initialise USART2 for 9600-8N1 command reception.
 *        [SWE-REQ-015, SWE-REQ-020]
 */
static void MX_USART2_UART_Init(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();

    /* PA2 = TX, PA3 = RX (Alternate Function AF7) */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance          = USART2;
    huart2.Init.BaudRate     = 9600U;
    huart2.Init.WordLength   = UART_WORDLENGTH_8B;
    huart2.Init.StopBits     = UART_STOPBITS_1;
    huart2.Init.Parity       = UART_PARITY_NONE;
    huart2.Init.Mode         = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    (void)HAL_UART_Init(&huart2);
}

/* ---------- Private: ADC init ---------- */

/**
 * @brief Initialise ADC1 Channel 1 (PA1) for potentiometer feedback.
 *        12-bit resolution, single conversion, software trigger.
 *        [SWE-REQ-017, SWE-REQ-020]
 */
static void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    __HAL_RCC_ADC1_CLK_ENABLE();

    /* PA1 as analog input */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    hadc1.Instance                   = ADC1;
    hadc1.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution            = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode          = DISABLE;
    hadc1.Init.ContinuousConvMode    = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion       = 1U;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
    (void)HAL_ADC_Init(&hadc1);

    sConfig.Channel      = ADC_CHANNEL_1;
    sConfig.Rank         = 1U;
    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    sConfig.Offset       = 0U;
    (void)HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

/* ---------- Private: Timer / PWM init ---------- */

/**
 * @brief Initialise TIM2 Channel 1 (PA0) for PWM motor-enable output.
 *        Frequency ~1 kHz with HSI @ 16 MHz: PSC=15, ARR=999 → 1 kHz.
 *        [SWE-REQ-016, SWE-REQ-020]
 */
static void MX_TIM2_Init(void)
{
    TIM_OC_InitTypeDef sConfigOC = {0};

    __HAL_RCC_TIM2_CLK_ENABLE();

    /* PA0 as TIM2_CH1 alternate function */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin       = GPIO_PIN_0;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    htim2.Instance               = TIM2;
    htim2.Init.Prescaler         = 15U;     /* 16 MHz / (15+1) = 1 MHz tick */
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = 999U;    /* 1 MHz / (999+1) = 1 kHz PWM  */
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    (void)HAL_TIM_PWM_Init(&htim2);

    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 0U;   /* Start at 0% duty (motor OFF) */
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    (void)HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
}

/* ---------- Public API ---------- */

/**
 * @brief Perform full system initialisation.
 *
 * Sequence:
 *   1. HAL_Init() and SystemClock_Config()
 *   2. Peripheral GPIO / UART / ADC / Timer-PWM init
 *   3. Initialise every software unit
 *   4. Ensure motor is OFF (safe state)
 *   5. Read initial feedback and indicate on LEDs
 *
 * [SWE-REQ-020, SWE-REQ-021]
 */
void SystemInit_Run(void)
{
    FeedbackResult_t initFb;

    /* 1. HAL and clock [SWE-REQ-020] */
    HAL_Init();
    SystemClock_Config();

    /* 2. Peripherals [SWE-REQ-020] */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM2_Init();

    /* 3. Software units [SWE-REQ-020] */
    MotorDriver_Init();         /* Motor first → safe state guaranteed */
    FeedbackProcessor_Init();
    CommandParser_Init();
    LedStatusHandler_Init();    /* Power LED ON here [SWE-REQ-012] */
    FlapControlLogic_Init();

    /* 4. Confirm motor is OFF [SWE-REQ-020] */
    MotorDriver_Stop();

    /* 5. Read initial feedback and set LEDs [SWE-REQ-021] */
    FeedbackProcessor_Update();
    initFb = FeedbackProcessor_GetPosition();
    if (initFb.valid == true)
    {
        LedStatusHandler_SetLedState(initFb.position);
    }
    else
    {
        LedStatusHandler_IndicateError();
    }
}
