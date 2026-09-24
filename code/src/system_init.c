/**
 * @file system_init.c
 * @brief System Startup / Initialisation implementation.
 *
 * Configures STM32F407 HAL, clocks, and all peripherals (UART, ADC, GPIO, PWM).
 * Initialises every software unit, reads initial feedback position, and sets LEDs.
 *
 * Traces: SWE-REQ-020, SWE-REQ-021
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "system_init.h"
#include "stm32f4xx_hal.h"

#include "command_parser.h"
#include "feedback_processor.h"
#include "flap_control_logic.h"
#include "led_status_handler.h"
#include "motor_driver.h"

/* ========================================================================= */
/*  Peripheral handle definitions (global, used by other units via extern)   */
/* ========================================================================= */

UART_HandleTypeDef huart2;
ADC_HandleTypeDef  hadc1;
TIM_HandleTypeDef  htim2;

/* ========================================================================= */
/*  Private: Clock configuration                                             */
/* ========================================================================= */

/**
 * @brief Configure system clocks for STM32F407 (HSE 8 MHz → 168 MHz).
 */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc_init = {0};
    RCC_ClkInitTypeDef clk_init = {0};

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc_init.HSEState       = RCC_HSE_ON;
    osc_init.PLL.PLLState   = RCC_PLL_ON;
    osc_init.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    osc_init.PLL.PLLM       = 8U;
    osc_init.PLL.PLLN       = 336U;
    osc_init.PLL.PLLP       = RCC_PLLP_DIV2;
    osc_init.PLL.PLLQ       = 7U;
    (void)HAL_RCC_OscConfig(&osc_init);

    clk_init.ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                              RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
    clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
    (void)HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_5);
}

/* ========================================================================= */
/*  Private: GPIO initialisation                                             */
/* ========================================================================= */

/**
 * @brief Initialise GPIO clocks and pin configurations for LEDs and motor.
 */
static void GPIO_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    /* Enable GPIO clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* --- Motor direction pins PB0, PB1 (output push-pull) --- */
    gpio.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);

    /* --- Power LED PD12 (output push-pull) --- */
    gpio.Pin   = GPIO_PIN_12;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &gpio);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    /* --- Position LEDs PE0..PE4 (output push-pull) --- */
    gpio.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &gpio);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);
}

/* ========================================================================= */
/*  Private: UART2 initialisation                                            */
/* ========================================================================= */

/**
 * @brief Initialise UART2 for command reception (115200-8-N-1).
 */
static void UART2_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_USART2_CLK_ENABLE();

    /* PA2 = TX, PA3 = RX (AF7 – USART2) */
    gpio.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    gpio.Mode      = GPIO_MODE_AF_PP;
    gpio.Pull      = GPIO_PULLUP;
    gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &gpio);

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

/* ========================================================================= */
/*  Private: ADC1 initialisation (potentiometer on PC0 / ADC1_IN10)          */
/* ========================================================================= */

/**
 * @brief Initialise ADC1 channel 10 for potentiometer feedback.
 */
static void ADC1_Init(void)
{
    GPIO_InitTypeDef gpio = {0};
    ADC_ChannelConfTypeDef adc_ch = {0};

    __HAL_RCC_ADC1_CLK_ENABLE();

    /* PC0 = ADC1_IN10 (analog) */
    gpio.Pin  = GPIO_PIN_0;
    gpio.Mode = GPIO_MODE_ANALOG;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &gpio);

    hadc1.Instance                   = ADC1;
    hadc1.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution            = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode          = DISABLE;
    hadc1.Init.ContinuousConvMode    = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion       = 1U;
    (void)HAL_ADC_Init(&hadc1);

    adc_ch.Channel      = ADC_CHANNEL_10;
    adc_ch.Rank         = 1U;
    adc_ch.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    (void)HAL_ADC_ConfigChannel(&hadc1, &adc_ch);
}

/* ========================================================================= */
/*  Private: TIM2 PWM initialisation (PA0 / TIM2_CH1)                       */
/* ========================================================================= */

/**
 * @brief Initialise TIM2 channel 1 for motor PWM (1 kHz, PA0).
 */
static void TIM2_PWM_Init(void)
{
    GPIO_InitTypeDef gpio = {0};
    TIM_OC_InitTypeDef oc_init = {0};

    __HAL_RCC_TIM2_CLK_ENABLE();

    /* PA0 = TIM2_CH1 (AF1) */
    gpio.Pin       = GPIO_PIN_0;
    gpio.Mode      = GPIO_MODE_AF_PP;
    gpio.Pull      = GPIO_NOPULL;
    gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* TIM2 base: 84 MHz / 84 = 1 MHz tick, period 1000 → 1 kHz PWM */
    htim2.Instance               = TIM2;
    htim2.Init.Prescaler         = 83U;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = 999U;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    (void)HAL_TIM_PWM_Init(&htim2);

    oc_init.OCMode     = TIM_OCMODE_PWM1;
    oc_init.Pulse      = 0U;  /* Start at 0% duty */
    oc_init.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc_init.OCFastMode = TIM_OCFAST_DISABLE;
    (void)HAL_TIM_PWM_ConfigChannel(&htim2, &oc_init, TIM_CHANNEL_1);
}

/* ========================================================================= */
/*  Public API                                                               */
/* ========================================================================= */

void SystemInit_Run(void)
{
    /* --- HAL and clock init --- */
    (void)HAL_Init();
    SystemClock_Config();

    /* --- Peripheral initialisation --- */
    GPIO_Init();
    UART2_Init();
    ADC1_Init();
    TIM2_PWM_Init();

    /* --- Software unit initialisation (SWE-REQ-020) --- */
    CommandParser_Init();
    FeedbackProcessor_Init();
    FlapControl_Init();
    LedStatus_Init();
    MotorDriver_Init();

    /* --- SWE-REQ-021: read initial feedback and indicate on LEDs --- */
    {
        uint8_t init_pos   = 0U;
        uint8_t init_valid = 0U;

        FeedbackProcessor_Update();
        FeedbackProcessor_GetPosition(&init_pos, &init_valid);

        if (init_valid == FB_VALID)
        {
            LedStatus_SetPosition(init_pos);
        }
        else
        {
            LedStatus_IndicateError();
        }
    }

    /* --- SWE-REQ-012: power LED on --- */
    LedStatus_SetPowerLed();
}
