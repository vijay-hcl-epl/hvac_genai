#ifndef INIT_POWERUP_SUPERVISOR_H
#define INIT_POWERUP_SUPERVISOR_H

#include <stdint.h>

typedef struct {
    uint8_t adc_handle;
    uint8_t uart_handle;
    uint8_t gpio_state;
    uint8_t pwm_config;
    uint8_t motor_status; /* 0: OFF, 1: ON */
    uint16_t pot_value;
    uint8_t power_led_state;
    uint8_t pos_led_state[6];
} init_powerup_supervisor_t;

typedef enum {
    PERIPHERALS_NOT_INITIALIZED,
    PERIPHERALS_INITIALIZED
} peripheral_state_e;

typedef enum {
    MOTOR_UNKNOWN,
    MOTOR_OFF
} motor_init_state_e;

typedef enum {
    FLAPPOSITION_UNKNOWN,
    FLAPPOSITION_INITIALIZED
} flap_init_state_e;

typedef enum {
    LEDS_UNSET,
    LEDS_INITIALIZED
} leds_init_state_e;

void init_powerup_supervisor_resp_1(init_powerup_supervisor_t *ctx);
void init_powerup_supervisor_resp_2(init_powerup_supervisor_t *ctx);
void init_powerup_supervisor_resp_3(init_powerup_supervisor_t *ctx);
void init_powerup_supervisor_resp_4(init_powerup_supervisor_t *ctx);

#endif
