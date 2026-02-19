#include "system_init.h"

void system_init(hvac_context_t *ctx, uint8_t initial_pos)
{
    if (ctx == NULL) { return; }
    command_parser_init(&ctx->cmd);
    feedback_processor_init(&ctx->fb);
    flap_control_init(&ctx->flap, initial_pos);
    motor_driver_init(&ctx->motor);
    led_status_init(&ctx->led);
    led_status_power_ok(&ctx->led);
}
