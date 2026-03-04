#include "CommandHandler.h"
#include "FlapControlLogic.h"

#define CMD_FRAME_SIZE 3
static uint8_t rx_buf[CMD_FRAME_SIZE];
static uint8_t rx_index = 0;

static bool is_valid_command(uint8_t *frame) {
    // Assume: frame[0] = start-byte, frame[1] = position, frame[2] = checksum
    if(frame[0] != 0xA5) return false;
    if(frame[1] >= FLAP_POS_MAX) return false;
    if(((frame[0] ^ frame[1]) != frame[2])) return false;
    return true;
}

void CommandHandler_Init(void) {
    rx_index = 0;
    for(uint8_t i = 0; i < CMD_FRAME_SIZE; ++i) rx_buf[i] = 0;
}

void CommandHandler_UART_ByteReceived(uint8_t byte) {
    if (rx_index == 0 && byte != 0xA5) return; // Start byte
    rx_buf[rx_index++] = byte;
    if (rx_index >= CMD_FRAME_SIZE) {
        if(is_valid_command(rx_buf)) {
            enum FlapPosition pos = (enum FlapPosition)rx_buf[1];
            if (pos > FLAP_POS_INVALID && pos < FLAP_POS_MAX) {
                FlapControlLogic_OnCommand(pos);
            }
        }
        rx_index = 0;
    }
}
