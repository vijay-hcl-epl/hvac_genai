#include "PosFeedback.h"
#include "hw_abstraction.h"
#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
static const uint16_t adc_ranges[6][2] = {
    { 100, 350 }, // Pos 0
    { 351, 600 }, // Pos 1
    { 601, 850 }, // Pos 2
    { 851, 1100}, // Pos 3
    { 1101, 1350},// Pos 4
    { 1351, 1600} // Pos 5
};
static uint16_t last_adc = 0;
uint8_t PosFeedback_GetPosition(void) {
    last_adc = hw_adc_read();
    for (uint8_t i = FLAP_POS_MIN; i <= FLAP_POS_MAX; ++i) {
        if (last_adc >= adc_ranges[i][0] && last_adc <= adc_ranges[i][1]) {
            return i;
        }
    }
    return 0xFF; // Out of range
}
bool PosFeedback_InRange(void) {
    uint8_t pos = PosFeedback_GetPosition();
    return (pos != 0xFF);
}
void PosFeedback_Init(void) {
    // ADC setup if required
}
