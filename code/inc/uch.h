#ifndef UCH_H_
#define UCH_H_
#include <stdint.h>
#include <stdbool.h>
// Command parse results
typedef enum { CMD_OK, CMD_OUT_OF_RANGE, CMD_INVALID } uch_cmd_result_t;
// API: get parsed command if available
bool uch_get_valid_command(uint8_t* val);
// Init function
typedef struct {
    uint8_t buffer;
    uch_cmd_result_t parse_result;
    bool new_command;
    uint8_t command_val;
} uch_cmd_ctx_t;
void uch_init(uch_cmd_ctx_t* ctx);
void uch_uart_rx_handler(uch_cmd_ctx_t* ctx, uint8_t ascii_byte);
#endif
