/**
 * @file system_init.c
 * @brief System Startup / Initialisation implementation.
 *
 * Software Unit : System Startup/Initialization
 * Traceability  : SWE-REQ-020, SWE-REQ-021
 *
 * Platform      : STM32F407G-DISC1, STM32 HAL, bare-metal
 *
 * CONFIGURATION GAP: All peripheral instance selections (USART2, ADC1,
 * TIM2, GPIO ports/pins) are ASSUMED placeholders matching common
 * STM32F407 Discovery board examples.  They MUST be cross-checked
 * against the actual project schematic and STM32CubeMX configuration
 * before deployment.
 *
 * Peripheral assumptions:
 *   UART  : USART2 – PA2 (TX), PA3 (RX), 115200 baud, 8N1
 *   ADC   : ADC1, Channel 1 (PA1), 12-bit, single conversion
 *   PWM   : TIM2, Channel 1 (PA0), 1 kHz, up-counting
 *   Motor : IN1=PB0, IN2=PB1 (push-pull outputs)
 *   LEDs  : Power=PD12; Position 0-4 = PE0..PE4 (push-pull outputs)
 */

#include "system_init.h"
#include "stm32f4xx_hal.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "flap_control_logic.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ── Peripheral handles (global, used by other units) ────────────────── */
UART_HandleTypeDef  huart2;
ADC_HandleTypeDef   hadc1;
TIM_HandleTypeDef   htim2;

/* ── Clock configuration (internal helper) ───────────────────────────── */

/**
 * @brief Configure system clocks.
 *
 * Uses HSI (16 MHz) as PLL source → SYSCLK = 168 MHz (typical for
 * STM32F407).
 *
 * CONFIGURATION GAP: PLL multipliers/dividers are typical defaults.
 * Adjust if a different clock tree is required.
 */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef rcc_osc = {0};
    RCC_ClkInitTypeDef rcc_clk = {0};

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* HSI oscillator, PLL ON */
    rcc_osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    rcc_osc.HSIState       = RCC_HSI_ON;
    rcc_osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    rcc_osc.PLL.PLLState   = RCC_PLL_ON;
    rcc_osc.PLL.PLLSource  = RCC_PLLSOURCE_HSI;
    rcc_osc.PLL.PLLM       = 8U;
    rcc_osc.PLL.PLLN       = 168U;
    rcc_osc.PLL.PLLP       = RCC_PLLP_DIV2;
    rcc_osc.PLL.PLLQ       = 7U;
    (void)HAL_RCC_OscConfig(&rcc_osc);

    /* Select PLL as SYSCLK, configure bus clocks */
    rcc_clk.ClockType      = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK
                           | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    rcc_clk.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    rcc_clk.APB1CLKDivider = RCC_HCLK_DIV4;
    rcc_clk.APB2CLKDivider = RCC_HCLK_DIV2;
    (void)HAL_RCC_ClockConfig(&rcc_clk, FLASH_LATENCY_5);
}

/* ── GPIO initialisation ─────────────────────────────────────────────── */

static void GPIO_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    /* Enable GPIO clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* ── Motor direction pins: PB0 (IN1), PB1 (IN2) ────────────────── */
    gpio.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);

    /* ── Power LED: PD12 ────────────────────────────────────────────── */
    gpio.Pin   = GPIO_PIN_12;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &gpio);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    /* ── Position LEDs: PE0 .. PE4 ──────────────────────────────────── */
    gpio.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
               | GPIO_PIN_3 | GPIO_PIN_4;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &gpio);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
                             | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);
}

/* ── UART initialisation (USART2, PA2/PA3, 115200 8N1) ──────────────── */

static void UART_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_USART2_CLK_ENABLE();

    /* PA2 = TX, PA3 = RX, AF7 */
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

/* ── ADC initialisation (ADC1, Channel 1, PA1, 12-bit) ──────────────── */

static void ADC_Init(void)
{
    GPIO_InitTypeDef     gpio    = {0};
    ADC_ChannelConfTypeDef ch_cfg = {0};

    __HAL_RCC_ADC1_CLK_ENABLE();

    /* PA1 = analog input */
    gpio.Pin  = GPIO_PIN_1;
    gpio.Mode = GPIO_MODE_ANALOG;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio);

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

    ch_cfg.Channel      = ADC_CHANNEL_1;
    ch_cfg.Rank         = 1U;
    ch_cfg.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    ch_cfg.Offset       = 0U;
    (void)HAL_ADC_ConfigChannel(&hadc1, &ch_cfg);
}

/* ── Timer / PWM initialisation (TIM2 CH1, PA0, 1 kHz) ──────────────── */

static void PWM_Init(void)
{
    GPIO_InitTypeDef         gpio   = {0};
    TIM_OC_InitTypeDef       oc_cfg = {0};
    TIM_MasterConfigTypeDef  master = {0};

    __HAL_RCC_TIM2_CLK_ENABLE();

    /* PA0 = TIM2_CH1 AF1 */
    gpio.Pin       = GPIO_PIN_0;
    gpio.Mode      = GPIO_MODE_AF_PP;
    gpio.Pull      = GPIO_NOPULL;
    gpio.Speed     = GPIO_SPEED_FREQ_LOW;
    gpio.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* TIM2 base: APB1 timer clock = 84 MHz (SYSCLK/2*2 for timers on APB1).
     * Prescaler 83 → 1 MHz tick, Period 999 → 1 kHz PWM.
     * CONFIGURATION GAP: PWM frequency must be confirmed for the L298N
     * and motor combination.                                             */
    htim2.Instance               = TIM2;
    htim2.Init.Prescaler         = 83U;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = 999U;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    (void)HAL_TIM_PWM_Init(&htim2);

    master.MasterOutputTrigger = TIM_TRGO_RESET;
    master.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
    (void)HAL_TIMEx_MasterConfigSynchronization(&htim2, &master);

    oc_cfg.OCMode     = TIM_OCMODE_PWM1;
    oc_cfg.Pulse      = 0U;
    oc_cfg.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc_cfg.OCFastMode = TIM_OCFAST_DISABLE;
    (void)HAL_TIM_PWM_ConfigChannel(&htim2, &oc_cfg, TIM_CHANNEL_1);
}

/* ── Public API ──────────────────────────────────────────────────────── */

void System_Init(void)
{
    /* 1. HAL base init (SysTick, NVIC priority grouping). */
    (void)HAL_Init();

    /* 2. System clock configuration. */
    SystemClock_Config();

    /* 3. Peripheral initialisation. */
    GPIO_Init();
    UART_Init();
    ADC_Init();
    PWM_Init();

    /* 4. Software-unit initialisation. */
    CmdParser_Init();
    FbProc_Init();
    FlapCtrl_Init();
    MotorDrv_Init();      /* Ensures motor is OFF (SWE-REQ-020). */
    LedStatus_Init();     /* Power LED ON, position LEDs OFF.    */

    /* 5. Read initial feedback and indicate on LEDs (SWE-REQ-021). */
    {
        FbProc_Result_t fb;
        FbProc_Update();
        FbProc_GetPosition(&fb);

        if (fb.valid != 0U)
        {
            LedStatus_SetPosition(fb.position);
        }
        else
        {
            LedStatus_IndicateError();
        }
    }
}
