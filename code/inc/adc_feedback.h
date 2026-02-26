// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf ADC10, 21.4 Register Description, p.387+
#ifndef ADC_FEEDBACK_H
#define ADC_FEEDBACK_H
#include <stdint.h>
typedef struct { uint16_t thresholds[6]; uint16_t sample_rate_hz; } ADCConfig;
int IADCFeedback_getPosition(uint8_t* position);
#endif
