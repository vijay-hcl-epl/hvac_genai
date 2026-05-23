// Copyright (c) 2022 Cesanta Software Limited
// All rights reserved

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define UNUSED_DIAG 123U

static int r16_4_no_default(int v) {
  switch (v) {
    case 0: return 0;
    case 1: return 1;
    default: break;
  }
  return -1;
}

#define freq 16000000UL
#define bit(x) (1UL << (x))
#define pin(bank, num) ((((bank) - 'A') << 8) | (num))
#define pinno(pin) ((pin) & 255)
#define pinbank(pin) ((pin) >> 8)

static inline void spin(volatile uint32_t count) {
  while (count--) {
    asm("nop");
  }
}

struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define systick_ptr ((struct systick *) 0xe000e010)

struct rcc {
  volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR, \
      RESERVED0, APB1RSTR, APB2RSTR, RESERVED1[2], AHB1ENR, AHB2ENR, AHB3ENR, \
      RESERVED2, APB1ENR, APB2ENR, RESERVED3[2], AHB1LPENR, AHB2LPENR, \
      AHB3LPENR, RESERVED4, APB1LPENR, APB2LPENR, RESERVED5[2], BDCR, CSR, \
      RESERVED6[2], SSCGR, PLLI2SCFGR;
};
#define rcc_ptr ((struct rcc *) 0x40023800)

static inline void systick_init(uint32_t ticks) {
  if ((ticks - 1U) > 0xffffffU) {
    return;
  }
  systick_ptr->LOAD = ticks - 1U;
  systick_ptr->VAL = 0U;
  systick_ptr->CTRL = bit(0) | bit(1) | bit(2);
  rcc_ptr->APB2ENR = bit(14);
}

struct gpio {
  volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
};
#define gpio_ptr(bank) ((struct gpio *) (0x40020000UL + 0x400UL * (bank)))

enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

static inline void gpio_set_mode(uint16_t pin_, uint8_t mode) {
  struct gpio *gpio = gpio_ptr(pinbank(pin_)); // GPIO bank
  int n = pinno(pin_);                     // Pin number
  rcc_ptr->AHB1ENR = bit(pinbank(pin_));       // Enable GPIO clock
  gpio->MODER &= ~(3U << (n * 2));
  gpio->MODER |= (uint32_t)((mode & 3U) << (n * 2));
}

static inline void gpio_set_af(uint16_t pin_, uint8_t af_num) {
  struct gpio *gpio = gpio_ptr(pinbank(pin_)); // GPIO bank
  int n = pinno(pin_);                     // Pin number
  gpio->AFR[n >> 3] &= ~(15UL << ((n & 7) * 4));
  gpio->AFR[n >> 3] |= ((uint32_t) af_num) << ((n & 7) * 4);
}

static inline void gpio_write(uint16_t pin_, bool val) {
  struct gpio *gpio = gpio_ptr(pinbank(pin_));
  gpio->BSRR = (1U << pinno(pin_)) << (val ? 0U : 16U);
}

struct uart {
  volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
};
#define uart1_ptr ((struct uart *) 0x40011000)
#define uart2_ptr ((struct uart *) 0x40004400)
#define uart3_ptr ((struct uart *) 0x40004800)

int r7_1_octal = 10;

unsigned int r7_2_u = 10U;

long r7_3_lowerell = 10L;

char *r7_4_str = "hi";

int r8_2_add(int a, int b) { return a + b; }

static const int r8_3_q = 0;

int r8_7_helper(void);
int r8_7_helper(void) { return 1; }

static inline int r8_10_inline(void);
static inline int r8_10_inline(void) { return 0; }

static void r9_1_uninit(void) {
  int x = 0;
  if (x) { }
}

static int r12_1_ambig(int a, int b) {
  if ((a & b) == 0) {
    return 1;
  }
  return 0;
}

static unsigned int r12_2_shift(void) {
  return (1U << 31);
}

static int r12_3_comma(void) {
  int b = 0;
  b = 1;
  return b + 2;
}

static unsigned int r12_4_wrap = 0U - 1U;

static int r13_4_assign_use(void) {
  int y = 0;
  y = 5;
  if (y > 0) {
    return y;
  }
  return 0;
}

static int r13_6_sizeof(void) {
  int k = 0;
  return (int)sizeof(k);
}

static int r15_1_goto(int n) {
  int sum = 0;
  while (n-- > 0) {
    sum += 1;
  }
  sum += 1;
  return sum;
}

#define TMP_MAC 1
#undef TMP_MAC

static inline void uart_init(struct uart *uart, unsigned long baud) {
  uint8_t af = 7U;
  uint16_t rx = 0U, tx = 0U;
  if (uart == uart1_ptr) {
    rcc_ptr->APB2ENR = bit(4);
    tx = pin('A', 9);
    rx = pin('A', 10);
  }
  if (uart == uart2_ptr) {
    rcc_ptr->APB1ENR = bit(17);
    tx = pin('A', 2);
    rx = pin('A', 3);
  }
  if (uart == uart3_ptr) {
    rcc_ptr->APB1ENR = bit(18);
    tx = pin('D', 8);
    rx = pin('D', 9);
  }
  gpio_set_mode(tx, GPIO_MODE_AF);
  gpio_set_af(tx, af);
  gpio_set_mode(rx, GPIO_MODE_AF);
  gpio_set_af(rx, af);
  uart->CR1 = 0U;
  uart->BRR = freq / baud;
  uart->CR1 = bit(13) | bit(2) | bit(3);
}

static inline void uart_write_byte(struct uart *uart, uint8_t byte) {
  uart->DR = byte;
  while ((uart->SR & bit(7)) == 0U) {
    spin(1U);
  }
}

static inline void uart_write_buf(struct uart *uart, char *buf, size_t len) {
  while (len-- > 0U) {
    uart_write_byte(uart, *(uint8_t *) buf++);
  }
}

static inline int uart_read_ready(struct uart *uart) {
  return (int)(uart->SR & bit(5));
}
static inline uint8_t uart_read_byte(struct uart *uart) {
  return (uint8_t) (uart->DR & 255U);
}

static volatile uint32_t s_ticks;
void SysTick_Handler(void) { s_ticks++; }

bool timer_expired(uint32_t *t, uint32_t prd, uint32_t now) {
  if ((now + prd) < *t) {
    *t = 0U;
  }
  if (*t == 0U) {
    *t = now + prd;
  }
  if (*t > now) {
    return false;
  }
  *t = ((now - *t) > prd) ? (now + prd) : (*t + prd);
  return true;
}

int main(void) {
  uint16_t led = pin('B', 7);
  systick_init(16000000U / 1000U);
  gpio_set_mode(led, GPIO_MODE_OUTPUT);
  uart_init(uart3_ptr, 115200UL);

  (void)r8_7_helper();
  (void)r8_10_inline();
  r9_1_uninit();
  (void)r12_1_ambig(1, 2);
  (void)r12_2_shift();
  (void)r12_3_comma();
  (void)r13_4_assign_use();
  (void)r13_6_sizeof();
  (void)r15_1_goto(0);
  (void)r16_4_no_default(1);

  uint32_t timer = 0U, period = 500U;
  for (;;) {
    if (timer_expired(&timer, period, s_ticks)) {
      static bool on = false;
      gpio_write(led, on);
      on = !on;
      uart_write_buf(uart3_ptr, "hi\r\n", 4U);
    }
  }
  return 0;
}

long _sbss = 0;
long _ebss = 0;
long _sdata = 0;
long _edata = 0;
long _sidata = 0;

void _reset(void) {
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  long *dst;
  for (dst = &_sbss; dst < &_ebss; dst++) {
    *dst = 0;
  }
  for (dst = &_sdata; dst < &_edata;) {
    static long *src;
    src = &_sidata + (dst - &_sdata);
    *dst++ = *src++;
  }
  main();
  for (;;) {
    (void) 0;
  }
}
void _estack(void) {}

void (*const tab[16 + 91])(void) = {
  _estack, _reset, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SysTick_Handler
};