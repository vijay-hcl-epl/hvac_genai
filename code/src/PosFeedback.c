#include "PosFeedback.h"
#include "hw_abstraction.h"
#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
static const uint16_t adc_ranges[6][2] = {
    { 100U, 350U }, /* MISRA: Rule 10.3 – Use unsigned constants */
    { 351U, 600U },
    { 601U, 850U },
    { 851U, 1100U },
    { 1101U, 1350U },
    { 1351U, 1600U }
};
static uint16_t last_adc = 0U;
uint8_t PosFeedback_GetPosition(void) {
    last_adc = hw_adc_read();
    for (uint8_t i = FLAP_POS_MIN; i <= FLAP_POS_MAX; ++i) {
        if ((last_adc >= adc_ranges[i][0]) && (last_adc <= adc_ranges[i][1])) { /* MISRA: Rule 12.1 – Enclose logical AND in parentheses */
            return i;
        }
    }
    return 0xFFU; /* MISRA: Rule 10.3 – Unsigned constant for unsigned var */
}
bool PosFeedback_InRange(void) {
    uint8_t pos = PosFeedback_GetPosition();
    return (pos != 0xFFU); /* MISRA: Rule 12.1 – Enclose expressions in parentheses */
}
void PosFeedback_Init(void) {
    /* ADC setup if required */
}
