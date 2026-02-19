#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdint.h>
#include "command_parser.h"
#include "flap_control.h"
#include "motor_driver.h"
#include "feedback_processor.h"
#include "led_status.h"

typedef struct {
    command_parser_t cmd;
    flap_control_t flap;
    motor_driver_t motor;
    feedback_processor_t fb;
    led_status_t led;
} hvac_context_t;

void system_init(hvac_context_t *ctx, uint8_t initial_pos);

#endif /* SYSTEM_INIT_H */
