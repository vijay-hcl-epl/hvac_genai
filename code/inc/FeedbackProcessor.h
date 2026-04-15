#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

#define FEEDBACK_ADC_MIN 100U
#define FEEDBACK_ADC_MAX 4000U

typedef struct {
    uint16_t adc_value;
    uint8_t position;
    bool valid;
} FeedbackProcessor_Data_t;

void FeedbackProcessor_Init(void);
void FeedbackProcessor_Update(void);
FeedbackProcessor_Data_t FeedbackProcessor_GetPosition(void);

#endif /* FEEDBACK_PROCESSOR_H */
