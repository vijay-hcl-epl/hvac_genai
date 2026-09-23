/**
 * @file system_init.c
 * @brief System Startup / Initialisation – HAL, clocks, peripherals, unit init.
 *
 * Software Unit: System Startup/Initialization
 * Traces: SWE-REQ-020, SWE-REQ-021
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 *
 * Peripheral Configuration:
 *   USART2  – UART command input (PC via USB-to-UART)
 *   ADC1    – Potentiometer feedback (PA1, Channel 1)
 *   TIM2    – PWM for motor enable (PA0, Channel 1)
 *   GPIOB   – Motor direction pins (PB0 = IN1, PB1 = IN2)
 *   GPIOD   – Power LED (PD12), Position LEDs 1-3 (PD13, PD14, PD15)
 *   GPIOE   – Position LEDs 4-5 (PE2, PE3)
 */

#include "system_init.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "flap_control_logic.h"
#include "motor_driver.h"
#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---------- Peripheral handles (global, used by other units) ------------ */

UART_HandleTypeDef huart2;
ADC_HandleTypeDef  hadc1;
TIM_HandleTypeDef  htim2;

/* ---------- Static clock configuration ---------------------------------- */

/**
 * @brief Configure the system clock (HSE, PLL to 168 MHz).
 */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* HSE oscillator, PLL configuration */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM       = 8U;
    RCC_OscInitStruct.PLL.PLLN       = 336U;
    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ       = 7U;
    (void)HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* AHB, APB1, APB2 clock dividers */
    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                       RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    (void)HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

/* ---------- Peripheral init helpers ------------------------------------- */

/**
 * @brief Initialise USART2 for UART command reception.
 *        PA2 = TX, PA3 = RX, 115200 baud, 8N1.
 */
static void MX_USART2_UART_Init(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance          = USART2;
    huart2.Init.BaudRate     = 115200U;
    huart2.Init.WordLength   = UART_WORDLENGTH_8B;
    huart2.Init.StopBits     = UART_STOPBITS_1;
    huart2.Init.Parity       = UART_PARITY_NONE;
    huart2.Init.Mode         = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    (void)HAL_UART_Init(&huart2);
}

/**
 * @brief Initialise ADC1, Channel 1 (PA1) for potentiometer feedback.
 *        12-bit resolution, single conversion.
 */
static void MX_ADC1_Init(void)
{
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    hadc1.Instance                   = ADC1;
    hadc1.Init.Resolution            = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode          = DISABLE;
    hadc1.Init.ContinuousConvMode    = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion       = 1U;
    (void)HAL_ADC_Init(&hadc1);

    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel      = ADC_CHANNEL_1;
    sConfig.Rank         = 1U;
    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    (void)HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

/**
 * @brief Initialise TIM2 Channel 1 (PA0) for PWM motor enable.
 *        1 kHz PWM frequency.
 */
static void MX_TIM2_PWM_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin       = GPIO_PIN_0;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 clock = APB1 * 2 = 84 MHz (APB1 = 42 MHz, timer multiplier x2)
     * Prescaler = 83 → timer clock = 1 MHz
     * Period    = 999 → PWM freq = 1 kHz */
    htim2.Instance               = TIM2;
    htim2.Init.Prescaler         = 83U;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = 999U;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    (void)HAL_TIM_PWM_Init(&htim2);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 0U;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    (void)HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
}

/**
 * @brief Initialise GPIO pins for motor direction (PB0, PB1) and LEDs (PD12-15, PE2-3).
 */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Motor direction pins: PB0 (IN1), PB1 (IN2) */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* LED pins on GPIOD: PD12 (power), PD13 (pos1), PD14 (pos2), PD15 (pos3) */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin   = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* LED pins on GPIOE: PE2 (pos4), PE3 (pos5) */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin   = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/* ---------- Public API -------------------------------------------------- */

void SystemInit_App(void)
{
    /* 1. HAL and clock initialisation */
    (void)HAL_Init();
    SystemClock_Config();

    /* 2. Peripheral initialisation */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM2_PWM_Init();

    /* 3. Software unit initialisation (motor off / safe state) [SWE-REQ-020] */
    MotorDriver_Init();
    LedStatusHandler_Init();
    FeedbackProcessor_Init();
    CommandParser_Init();
    FlapControlLogic_Init();

    /* 4. Read initial feedback and set LEDs [SWE-REQ-021] */
    FeedbackProcessor_Update();
    {
        FeedbackResult_t fb = FeedbackProcessor_GetPosition();
        if (fb.valid == true)
        {
            LedStatusHandler_SetLedState(fb.position);
        }
    }

    /* 5. Activate power LED [SWE-REQ-012] */
    LedStatusHandler_SetPowerLed();
}
