#include "status_output_if.h"

static StatusCode_t current_status = STATUS_IDLE;

void StatusOutputIF_Init(void) {
    current_status = STATUS_IDLE;
}

void StatusOutputIF_Set(StatusCode_t code) {
    current_status = code;
    // Set/clear LEDs as per code (hardware specific)
}
