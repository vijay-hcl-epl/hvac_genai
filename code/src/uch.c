#include "uch.h"
#include <ctype.h>
static uch_cmd_ctx_t g_uch_cmd_ctx = {0};
void uch_init(uch_cmd_ctx_t* ctx) {
    ctx->buffer = 0;
    ctx->parse_result = CMD_INVALID;
    ctx->new_command = false;
    ctx->command_val = 0;
}

void uch_uart_rx_handler(uch_cmd_ctx_t* ctx, uint8_t ascii_byte) {
    if (isdigit(ascii_byte)) {
        uint8_t val = ascii_byte - '0';
        if (val >= FLAP_POS_MIN && val <= FLAP_POS_MAX) {
            ctx->parse_result = CMD_OK;
            ctx->new_command = true;
            ctx->command_val = val;
            ctx->buffer = val;
        } else {
            ctx->parse_result = CMD_OUT_OF_RANGE;
        }
    } else {
        ctx->parse_result = CMD_INVALID;
    }
}

bool uch_get_valid_command(uint8_t* val) {
    if (g_uch_cmd_ctx.new_command) {
        *val = g_uch_cmd_ctx.command_val;
        g_uch_cmd_ctx.new_command = false;
        return true;
    }
    return false;
}
