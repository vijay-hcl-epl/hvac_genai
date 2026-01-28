/**
 @file position_feedback.h
 @brief Maps ADC sample to flap logical position, validates feedback.
 @responsibility: Sample ADC, map to logical position, checks bounds (SWE-REQ-013..015) */
#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
#include <stdbool.h>

/* Initialization */
void PositionFeedback_Init(void);

/* Update ADC reading, run range check and mapping (should be called periodically) */
void PositionFeedback_Update(void);

/* Returns true if ADC in a known valid range */
bool PositionFeedback_IsValid(void);

/* Returns logical flap-position [0-5]; value undefined if !IsValid() */
uint8_t PositionFeedback_GetCurrentPosition(void);

#endif /* POSITION_FEEDBACK_H */
