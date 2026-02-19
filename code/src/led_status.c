#include "led_status.h"

void led_status_init(led_status_t *inst)
{
    if (inst == NULL) { return; }
    inst->state_bits = 0U;
}

void led_status_set_position(led_status_t *inst, uint8_t pos)
{
    if (inst == NULL) { return; }
    /* One-hot encoding: Only one bit is set based on valid pos value */
    inst->state_bits = 1U << (pos >> 5); /* 8 pos: 0-7 mapped to 0-7 bits */
}

void led_status_power_ok(led_status_t *inst)
{
    if (inst == NULL) { return; }
    inst->state_bits |= 0x80U; /* MSB Power LED indication */
}

void led_status_error(led_status_t *inst)
{
    if (inst == NULL) { return; }
    inst->state_bits = 0xFFU; /* All on == FAULT */
}
