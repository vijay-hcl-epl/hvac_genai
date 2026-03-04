/* PositionFeedback.h - Reads and interprets ADC input for physical position feedback. */
#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

#include <stdint.h>
#include <stdbool.h>

#define FEEDBACK_ADC_MIN    100
#define FEEDBACK_ADC_MAX    900

uint8_t PositionFeedback_ReadPosition(void);
bool PositionFeedback_ErrorStatus(void);

#endif /* POSITION_FEEDBACK_H */
