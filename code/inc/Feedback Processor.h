#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Traces: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027, SWE-REQ-028, SWE-REQ-030, SWE-REQ-031, SWE-REQ-036, SWE-REQ-038 */

typedef enum
{
    HVAC_FLAP_POSITION_FACE = 0,
    HVAC_FLAP_POSITION_BI_LEVEL = 1,
    HVAC_FLAP_POSITION_FOOT = 2,
    HVAC_FLAP_POSITION_DEFROST = 3,
    HVAC_FLAP_POSITION_INVALID = 255
} Hvac_FlapPosition_t;

typedef enum
{
    FEEDBACK_PROCESSOR_STATE_INIT = 0,
    FEEDBACK_PROCESSOR_STATE_READY,
    FEEDBACK_PROCESSOR_STATE_INVALID
} FeedbackProcessor_State_t;

typedef struct
{
    bool valid;
    Hvac_FlapPosition_t position;
    uint16_t adc_sample;
} FeedbackProcessor_Position_t;

void FeedbackProcessor_Init(void);
void FeedbackProcessor_Update(void);
FeedbackProcessor_Position_t FeedbackProcessor_GetPosition(void);
FeedbackProcessor_State_t FeedbackProcessor_GetState(void);

#ifdef __cplusplus
}
#endif

#endif /* FEEDBACK_PROCESSOR_H */
