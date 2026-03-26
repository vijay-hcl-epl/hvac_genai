#include "configuration.h"
#include "error_handler.h"
static uint16_t thresholds[6] = {400, 800, 1200, 1600, 2000, 4095};
void Configuration_Init(void) {
    // Init from flash/NVM if needed
}
const uint16_t* Configuration_GetThresholds(void) {
    return thresholds;
}
