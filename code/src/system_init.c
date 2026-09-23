/**
 * @file    system_init.c
 * @brief   System Startup / Initialisation software unit – implementation.
 *
 * Configures STM32 HAL, system clock, and all peripherals (UART, ADC,
 * GPIO, Timer/PWM).  Then initialises every software unit and reads
 * the initial feedback to set LEDs.
 *
 * Traceability:
 *   SWE-REQ-020  – Initialise all device interfaces; motor OFF.
 *   SWE-REQ-021  – Read feedback and indicate initial state on LEDs.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 *
 * Peripheral Assignment:
 *   USART2 PA2/PA3   – UART command input (connected via USB-UART).
 *   ADC1   PA0       – Potentiometer feedback.
 *   TIM3   PA6 CH1   – PWM enable for L298N ENA.
 *   PB4, PB5         – Motor direction (IN1, IN2).
 *   PD12             – Power / run LED (on-board green).
 *   PE7..PE11        – Position LEDs 0..4 (external green LEDs).
 */

/* ---- Includes ------------------------------------------------------- */
#include "system_init.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "flap_control_logic.h"
#include "motor_driver.h"
#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---- Extern HAL Handles (defined in main.c) ------------------------- */
extern UART_HandleTypeDef  huart2;
extern ADC_HandleTypeDef   hadc1;
extern TIM_HandleTypeDef   htim3;

/* ---- Private: Clock Configuration ----------------------------------- */

/**
 * @brief  Configure system clock to 168 MHz using HSE + PLL (STM32F407).
 */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef       oscInit  = {0};
    RCC_ClkInitTypeDef       clkInit  = {0};

    /* Enable PWR clock and set voltage regulator scale. */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* HSE oscillator + PLL. */
    oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscInit.HSEState       = RCC_HSE_ON;
    oscInit.PLL.PLLState   = RCC_PLL_ON;
    oscInit.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    oscInit.PLL.PLLM       = 8U;
    oscInit.PLL.PLLN       = 336U;
    oscInit.PLL.PLLP       = RCC_PLLP_DIV2;
    oscInit.PLL.PLLQ       = 7U;
    (void)HAL_RCC_OscConfig(&oscInit);

    /* System / AHB / APB clocks. */
    clkInit.ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                             RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    clkInit.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clkInit.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
    clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
    (void)HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_5);
}

/* ---- Private: GPIO Initialisation ----------------------------------- */

/**
 * @brief  Configure all GPIO pins used by the application.
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef gpioInit = {0};

    /* Enable GPIO clocks. */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* Motor direction pins: PB4 (IN1), PB5 (IN2) – push-pull output. */
    gpioInit.Pin   = GPIO_PIN_4 | GPIO_PIN_5;
    gpioInit.Mode  = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull  = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpioInit);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);

    /* Power LED: PD12 – push-pull output. */
    gpioInit.Pin   = GPIO_PIN_12;
    gpioInit.Mode  = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull  = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &gpioInit);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    /* Position LEDs: PE7..PE11 – push-pull output. */
    gpioInit.Pin   = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
                     GPIO_PIN_10 | GPIO_PIN_11;
    gpioInit.Mode  = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull  = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &gpioInit);
    HAL_GPIO_WritePin(GPIOE,
                      GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
                      GPIO_PIN_10 | GPIO_PIN_11,
                      GPIO_PIN_RESET);
}

/* ---- Private: UART Initialisation ----------------------------------- */

/**
 * @brief  Configure USART2 for command reception (115200-8-N-1).
 */
static void MX_USART2_UART_Init(void)
{
    GPIO_InitTypeDef gpioInit = {0};

    __HAL_RCC_USART2_CLK_ENABLE();

    /* PA2 = TX, PA3 = RX (alternate function AF7). */
    gpioInit.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    gpioInit.Mode      = GPIO_MODE_AF_PP;
    gpioInit.Pull      = GPIO_PULLUP;
    gpioInit.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioInit.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &gpioInit);

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

/* ---- Private: ADC Initialisation ------------------------------------ */

/**
 * @brief  Configure ADC1 channel 0 (PA0) for potentiometer reading.
 */
static void MX_ADC1_Init(void)
{
    GPIO_InitTypeDef          gpioInit    = {0};
    ADC_ChannelConfTypeDef    chanConfig  = {0};

    __HAL_RCC_ADC1_CLK_ENABLE();

    /* PA0 as analog input. */
    gpioInit.Pin  = GPIO_PIN_0;
    gpioInit.Mode = GPIO_MODE_ANALOG;
    gpioInit.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpioInit);

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

    chanConfig.Channel      = ADC_CHANNEL_0;
    chanConfig.Rank         = 1U;
    chanConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    chanConfig.Offset       = 0U;
    (void)HAL_ADC_ConfigChannel(&hadc1, &chanConfig);
}

/* ---- Private: Timer / PWM Initialisation ---------------------------- */

/**
 * @brief  Configure TIM3 CH1 (PA6) as PWM output for motor ENA.
 *         PWM frequency ≈ 1 kHz at 84 MHz APB1 timer clock.
 */
static void MX_TIM3_Init(void)
{
    GPIO_InitTypeDef         gpioInit = {0};
    TIM_OC_InitTypeDef       ocConfig = {0};

    __HAL_RCC_TIM3_CLK_ENABLE();

    /* PA6 as TIM3_CH1 alternate function. */
    gpioInit.Pin       = GPIO_PIN_6;
    gpioInit.Mode      = GPIO_MODE_AF_PP;
    gpioInit.Pull      = GPIO_NOPULL;
    gpioInit.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpioInit.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOA, &gpioInit);

    htim3.Instance               = TIM3;
    htim3.Init.Prescaler         = 83U;      /* 84 MHz / 84 = 1 MHz tick  */
    htim3.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim3.Init.Period            = 999U;     /* 1 MHz / 1000 = 1 kHz PWM  */
    htim3.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    (void)HAL_TIM_PWM_Init(&htim3);

    ocConfig.OCMode     = TIM_OCMODE_PWM1;
    ocConfig.Pulse      = 0U;              /* Start with 0 % duty.       */
    ocConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    ocConfig.OCFastMode = TIM_OCFAST_DISABLE;
    (void)HAL_TIM_PWM_ConfigChannel(&htim3, &ocConfig, TIM_CHANNEL_1);
}

/* ---- Public API Implementation -------------------------------------- */

/* [SWE-REQ-020, SWE-REQ-021] */
void SystemInit_Run(void)
{
    uint8_t initPosition = 0U;

    /* ---- HAL & Clock ---- */
    (void)HAL_Init();
    SystemClock_Config();

    /* ---- Peripheral Init ---- */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM3_Init();

    /* ---- Software Unit Init (SWE-REQ-020) ---- */
    CommandParser_Init();
    FeedbackProcessor_Init();
    FlapControl_Init();
    MotorDriver_Init();       /* Ensures motor OFF. */
    LedStatus_Init();         /* All LEDs OFF.      */

    /* ---- Initial Feedback & LED State (SWE-REQ-021) ---- */
    FeedbackProcessor_Update();
    if (FeedbackProcessor_GetPosition(&initPosition) == true)
    {
        LedStatus_SetPosition(initPosition);
    }
    else
    {
        LedStatus_IndicateError();
    }

    /* Power / run LED ON (SWE-REQ-012). */
    LedStatus_SetPowerLed();
}
