#include "system_init_platform.h"
#include "feedback_processor.h"
static uint16_t static_calib[6] = {100, 600, 1100, 1600, 2100, 2700};

void SystemInit_All(void) {
    // Power-up peripheral, pin, and static config
    // (Mocks only; replace with real driver initialization)
    (void)static_calib;
}

const uint16_t* SystemInit_GetCalibration(void) {
    return static_calib;
}
