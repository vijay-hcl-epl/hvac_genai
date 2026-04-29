#include "input_handler.h"
#include "flap_control_logic.h"

#define FRAME_SIZE 3
#define POSITION_MAX 5
static uint8_t rx_buffer[FRAME_SIZE];
static uint8_t rx_count = 0;
static bool command_in_progress = false;

void input_handler_init(void) {
    rx_count = 0;
    command_in_progress = false;
}

void input_handler_rx_byte(uint8_t byte) {
    rx_buffer[rx_count++] = byte;
    if (rx_count == FRAME_SIZE) {
        // Assume [START][POS][END]; Simple demo convention
        bool valid = (rx_buffer[0] == 0xAA) && (rx_buffer[2] == 0xBB);
        uint8_t pos = rx_buffer[1];
        if (valid && pos < POSITION_MAX && !command_in_progress) {
            command_in_progress = true;
            flap_control_on_valid_position(pos);
        }
        rx_count = 0;
    }
}

void input_handler_test_inject(uint8_t *frame, uint8_t len) {
    if (len == FRAME_SIZE) {
        for (uint8_t i = 0; i < FRAME_SIZE; ++i) {
            input_handler_rx_byte(frame[i]);
        }
    }
}

void input_handler_command_complete(void) {
    command_in_progress = false;
}
