// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf ADC10 (21.4)
#include "adc_feedback.h"
#include "config_manager.h"
#include "error_handler.h"
#define ADC1_CON (*(volatile unsigned int*)0x40012000)
#define ADC1_CHSELR (*(volatile unsigned int*)0x40012004)
#define ADC1_RES (*(volatile unsigned int*)0x40012014)
static ADCConfig adc_cfg;
int IADCFeedback_getPosition(uint8_t* position) {
    ADC1_CON |= (1 << 0); // Start conversion
    while ((ADC1_CON & (1 << 0)) != 0); // wait ready
    uint16_t val = (uint16_t)ADC1_RES;
    for (uint8_t i = 0; i < 6; ++i) {
        if (val <= adc_cfg.thresholds[i]) {
            *position = i;
            return 0;
        }
    }
    IErrorHandler_notify(2, 2); // ADC fault
    return -1;
}
