#include "motor_indicator_interface.h"
#include <stdint.h>
#include <stdbool.h>

static uint8_t led_states[NUM_FLAP_POSITIONS] = {0};
static bool error_led = false;

// Dummy hardware abstraction functions (replace with MCU library/GPIO funcs)
static void gpio_set_motor_direction(motor_direction_t dir) {}
static void gpio_set_motor_enable(bool en) {}
static void gpio_set_led(uint8_t idx, bool on) {}
static void gpio_set_error_led(bool on) {}

void motor_indicator_interface_init(void)
{
    for (uint8_t i = 0; i < NUM_FLAP_POSITIONS; ++i)
        led_states[i] = 0;
    error_led = false;
    gpio_set_motor_enable(false);
    gpio_set_motor_direction(MOTOR_DIRECTION_NONE);
}

void motor_drive_request(motor_direction_t dir, bool enable)
{
    if (!enable || dir == MOTOR_DIRECTION_NONE)
    {
        gpio_set_motor_enable(false);
        gpio_set_motor_direction(MOTOR_DIRECTION_NONE);
        return;
    }
    if (dir == MOTOR_DIRECTION_FORWARD)
    {
        gpio_set_motor_direction(MOTOR_DIRECTION_FORWARD);
    }
    else if (dir == MOTOR_DIRECTION_REVERSE)
    {
        gpio_set_motor_direction(MOTOR_DIRECTION_REVERSE);
    }
    gpio_set_motor_enable(true);
}

void set_led_state(uint8_t position_index, bool error_flag)
{
    // Only one position LED on at a time
    for (uint8_t i = 0; i < NUM_FLAP_POSITIONS; ++i)
        gpio_set_led(i, false);
    if (position_index < NUM_FLAP_POSITIONS)
        gpio_set_led(position_index, true);
    // Error LED control
    error_led = error_flag;
    gpio_set_error_led(error_led);
}
