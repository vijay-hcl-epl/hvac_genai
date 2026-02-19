#include "system_init.h"
#include <stdint.h>
#include <stdbool.h>

/* Simulated UART/ADC interface function stubs */
static uint8_t UART_receive(void)    { return 0x20U; }
static uint16_t ADC_read(void)       { return 1000U; }
static bool UART_byte_available(void){ return true; }

int main(void)
{
    hvac_context_t ctx;
    uint8_t last_cmd = 0U;
    uint8_t curr_pos = 0U;
    uint16_t adc_val = 0U;
    bool valid_cmd = false, valid_fb = false, move = false;

    system_init(&ctx, 0x00U);

    while (1) {
        if (UART_byte_available()) {
            uint8_t rx = UART_receive();
            command_parser_process_byte(&ctx.cmd, rx);
        }
        valid_cmd = command_parser_get_latest(&ctx.cmd, &last_cmd);
        adc_val = ADC_read();
        valid_fb = feedback_processor_update(&ctx.fb, adc_val);
        move = flap_control_update(&ctx.flap, last_cmd, valid_cmd, ctx.fb.position, valid_fb);
        if (ctx.flap.state == FLAP_MOVING && move) {
            if (ctx.flap.target_position > ctx.flap.current_position) {
                motor_drive(&ctx.motor, MOTOR_DIR_FWD, true, 0x80U);
            } else {
                motor_drive(&ctx.motor, MOTOR_DIR_REV, true, 0x80U);
            }
        } else if (ctx.flap.state == FLAP_TARGET_REACHED) {
            motor_stop(&ctx.motor);
        } else if (ctx.flap.state == FLAP_FAULT) {
            motor_stop(&ctx.motor);
            led_status_error(&ctx.led);
        }
        led_status_set_position(&ctx.led, ctx.flap.current_position);
        /* Add watchdog, small delay, or idle here as per platform */
    }
    return 0;
}
