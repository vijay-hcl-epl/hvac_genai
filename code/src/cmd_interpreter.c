#include "cmd_interpreter.h"

int Cmd_decode(const uint8_t* rx, uint8_t* pos_val) {
    if (!rx) return -1; // null
    uint8_t v = *rx;
    if (v <= 5) {
        *pos_val = v; return 0;
    }
    return -2; // out of range
}
uint8_t Cmd_status(void) { return 0; }
