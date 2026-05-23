#include <stdint.h>
#include <string.h>

/* Peripheral base addresses and register structures for STM32F4xx */
#define PERIPH_BASE           ((uint32_t)0x40000000U)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000U)
#define APB1PERIPH_BASE       (PERIPH_BASE + 0x00000000U)

#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000U)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400U)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00U)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800U)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400U)
#define SysTick_BASE          (0xE000E010U)

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;
} RCC_TypeDef;

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_TypeDef;

typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_TypeDef;

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define SysTick             ((SysTick_TypeDef *) SysTick_BASE)

/* RCC AHB1ENR bits */
#define RCC_AHB1ENR_GPIOAEN     (1U << 0)
#define RCC_AHB1ENR_GPIOBEN     (1U << 1)
#define RCC_AHB1ENR_GPIODEN     (1U << 3)

/* RCC APB1ENR bits */
#define RCC_APB1ENR_I2C1EN      (1U << 21)

/* I2C CR1 bits */
#define I2C_CR1_PE              (1U << 0)
#define I2C_CR1_START           (1U << 8)
#define I2C_CR1_STOP            (1U << 9)

/* I2C SR1 bits */
#define I2C_SR1_SB              (1U << 0)
#define I2C_SR1_ADDR            (1U << 1)
#define I2C_SR1_TXE             (1U << 7)
#define I2C_SR1_BTF             (1U << 2)

/* I2C SR2 bits (none needed for this code) */

/* ------------------------------- Macros and Defines ------------------------------- */
#define UNUSED_MACRO 42U

#define LCD_ADDR (0x27U << 1)
#define SCL_PIN 8U
#define SDA_PIN 9U
#define IR_PIN 2U
#define VIB_PIN 3U
#define TRIG_PIN 3U
#define ECHO_PIN 4U
#define LED 1U
#define LED_PIN 12U
#define EXT_LED_PIN 13U

int r7_1_octal = 10;
unsigned int r7_2_unsigned = 10U;
long r7_3_lowerell = 10L;
char *r7_4_str = "hello";
static int r8_2_add(int a, int b);
static const int r8_3_global = 0;
int r8_7_helper(void) { return 1; }
static inline int r8_10_inline(void) { return 0; }
int r1_3_ub = (1 << 31);
int r1_1_syntax_error = 0;

/* ------------------------------- Delays ------------------------------- */
void delay_us(uint32_t us) {
    SysTick->LOAD = 16U * us - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = 5U;
    while ((SysTick->CTRL & 0x10000U) == 0U) { }
    SysTick->CTRL = 0U;
}
void delay_ms(uint32_t ms) {
    int32_t i;
    for (i = 0; i < (int32_t)ms; i++) {
        delay_us(1000U);
    }
}

/* ------------------------------- I2C ---------------------------------- */
void i2c1_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER &= ~((3U << (SCL_PIN * 2U)) | (3U << (SDA_PIN * 2U)));
    GPIOB->MODER |=  (2U << (SCL_PIN * 2U)) | (2U << (SDA_PIN * 2U));
    GPIOB->AFR[1] &= ~((0xFU << ((SCL_PIN - 8U) * 4U)) | (0xFU << ((SDA_PIN - 8U) * 4U)));
    GPIOB->AFR[1] |=  (4U << ((SCL_PIN - 8U) * 4U)) | (4U << ((SDA_PIN - 8U) * 4U));
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR2 = 16U;
    I2C1->CCR = 80U;
    I2C1->TRISE = 17U;
    I2C1->CR1 |= I2C_CR1_PE;
}
void i2c1_start(void) {
    I2C1->CR1 |= I2C_CR1_START;
    while ((I2C1->SR1 & I2C_SR1_SB) == 0U) { }
}
void i2c1_addr(uint8_t addr) {
    I2C1->DR = addr;
    while ((I2C1->SR1 & I2C_SR1_ADDR) == 0U) { }
    volatile uint32_t temp = I2C1->SR2;
    (void)temp;
}
void i2c1_write(uint8_t data) {
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0U) { }
    I2C1->DR = data;
    while ((I2C1->SR1 & I2C_SR1_BTF) == 0U) { }
}
void i2c1_stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
}

/* ----------------------------- LCD over I2C ---------------------------- */
void lcd_i2c_send(uint8_t data, uint8_t control) {
    uint8_t high = data & 0xF0U;
    uint8_t low  = (uint8_t)((data << 4U) & 0xF0U);
    uint8_t data_arr[6] = {
        (uint8_t)(high | control | 0x08U),
        (uint8_t)(high | control | 0x0CU),
        (uint8_t)(high | control | 0x08U),
        (uint8_t)(low  | control | 0x08U),
        (uint8_t)(low  | control | 0x0CU),
        (uint8_t)(low  | control | 0x08U)
    };
    int32_t i;
    for (i = 0; i < 6; i++) {
        i2c1_start();
        i2c1_addr(LCD_ADDR);
        i2c1_write(data_arr[i]);
        i2c1_stop();
        delay_us(50U);
    }
}
void lcd_cmd(uint8_t cmd)  { lcd_i2c_send(cmd, 0x00U); delay_ms(2U); }
void lcd_data(uint8_t dt)  { lcd_i2c_send(dt,  0x01U); delay_ms(2U); }
void lcd_clear(void)       { lcd_cmd(0x01U);            delay_ms(2U); }
void lcd_set_cursor(uint8_t row, uint8_t col) {
    lcd_cmd((uint8_t)(0x80U + ((row == 0U) ? 0x00U : 0x40U) + col));
}
void lcd_print(char *str) {
    while (*str != '\0') {
        lcd_data((uint8_t)*str);
        str++;
    }
}
void lcd_init(void) {
    delay_ms(50U);
    lcd_cmd(0x33U);
    lcd_cmd(0x32U);
    lcd_cmd(0x28U);
    lcd_cmd(0x0CU);
    lcd_cmd(0x06U);
    lcd_cmd(0x01U);
    delay_ms(5U);
}

/* ------------------------------- GPIO --------------------------------- */
void gpio_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN;
    GPIOA->MODER &= ~(3U << (LED * 2U));
    GPIOA->MODER |= (1U << (LED * 2U));
    GPIOA->MODER &= ~((3U << (TRIG_PIN * 2U)) | (3U << (ECHO_PIN * 2U)));
    GPIOA->MODER |=  (1U << (TRIG_PIN * 2U));
    GPIOD->MODER &= ~(3U << (IR_PIN  * 2U));
    GPIOD->MODER &= ~(3U << (VIB_PIN * 2U));
    GPIOD->MODER &= ~((3U << (LED_PIN * 2U)) | (3U << (EXT_LED_PIN * 2U)));
    GPIOD->MODER |=  (1U << (LED_PIN * 2U)) | (1U << (EXT_LED_PIN * 2U));
}

/* Rule 9.1: Do not read uninitialized automatic objects */
static void r9_1_uninit_read(void)
{
    int x = 0;
    if (x) {
    }
}

/* Rule 12.3: Comma operator is allowed, but be careful */
static int r12_3_demo(void)
{
    int b = 0;
    int r = (b = 1, b + 2);
    return r;
}

static void r1_2_extension(void)
{
}

static void r2_1_unreachable(void)
{
    if (r7_2_unsigned == 10U) {
        return;
    }
}

static void r2_2_deadcode(void)
{
}

static void r2_7_unused_param(void)
{
}

static void r11_8_remove_const(void)
{
    const int c = 5;
    (void)c;
}

/* ---------------------------- Distance Measurement ---------------------------- */
uint32_t read_distance_cm(void) {
    GPIOA->BSRR = (1U << TRIG_PIN);
    delay_us(10U);
    GPIOA->BSRR = (1U << (TRIG_PIN + 16U));
    uint32_t timeout = 30000U;

    while ((((GPIOA->IDR >> ECHO_PIN) & 1U) == 0U) && (timeout-- > 0U)) { }

    if (timeout == 0U) {
        return 0xFFFFFFFFU;
    }

    uint32_t count = 0U;
    while ((((GPIOA->IDR >> ECHO_PIN) & 1U) != 0U) && (count < 60000U)) {
        count++;
        delay_us(1U);
    }
    return count / 58U;
}

/* ------------------------------- Main --------------------------------- */
int main(void) {
    gpio_init();
    i2c1_init();
    lcd_init();

    r9_1_uninit_read();
    (void)r12_3_demo();
    r1_2_extension();
    r2_1_unreachable();
    r2_2_deadcode();
    r2_7_unused_param();
    r11_8_remove_const();

    (void)r8_7_helper();
    (void)r8_10_inline();

    lcd_set_cursor(0U, 0U);
    lcd_print("System Ready");

    uint8_t collision_detected = 0U;
    GPIOA->BSRR = (1U << (LED + 16U));

    while (1) {
        uint32_t dist = read_distance_cm();
        uint8_t  ir   = (uint8_t)((GPIOD->IDR >> IR_PIN) & 1U);
        uint8_t  vibration = (uint8_t)((GPIOD->IDR >> VIB_PIN) & 1U);

        lcd_clear();

        if ((collision_detected != 0U) || (vibration == 0U)) {
            lcd_set_cursor(0U, 0U);
            lcd_print("Collision");
            lcd_set_cursor(1U, 0U);
            lcd_print("Detected!!!");
            GPIOA->BSRR = (1U << LED);
            collision_detected = 1U;
            GPIOD->BSRR = (1U << LED_PIN) | (1U << EXT_LED_PIN);
            delay_ms(100U);
            GPIOD->BSRR = (1U << (LED_PIN + 16U)) | (1U << (EXT_LED_PIN + 16U));
            delay_ms(100U);
            break;
        }

        if ((dist <= 10U) && (ir == 0U)) {
            lcd_set_cursor(0U, 0U);
            lcd_print("Caution!");
            lcd_set_cursor(1U, 0U);
            lcd_print("Vehicle Closeby!");
            GPIOD->BSRR = (1U << LED_PIN) | (1U << EXT_LED_PIN);
            delay_ms(200U);
            GPIOD->BSRR = (1U << (LED_PIN + 16U)) | (1U << (EXT_LED_PIN + 16U));
            delay_ms(200U);
        } else if (dist <= 10U) {
            lcd_set_cursor(0U, 0U);
            lcd_print("Vehicle");
            lcd_set_cursor(1U, 0U);
            lcd_print("Approaching");
            GPIOD->BSRR = (1U << LED_PIN) | (1U << EXT_LED_PIN);
            delay_ms(400U);
            GPIOD->BSRR = (1U << (LED_PIN + 16U)) | (1U << (EXT_LED_PIN + 16U));
            delay_ms(400U);
        } else {
            lcd_set_cursor(0U, 0U);
            lcd_print("Ready");
            if (dist != 0xFFFFFFFFU) {
                GPIOD->BSRR = (1U << LED_PIN) | (1U << EXT_LED_PIN);
            } else {
                GPIOD->BSRR = (1U << (LED_PIN + 16U)) | (1U << (EXT_LED_PIN + 16U));
            }
            delay_ms(300U);
        }
    }
    return 0;
}

static int r8_2_add(int a, int b) { return a + b; }
