#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>
#include "Feedback Processor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039 */

typedef enum
{
    LED_STATUS_NORMAL = 0,
    LED_STATUS_ERROR = 1
} LedStatus_Mode_t;

void LedStatusHandler_Init(void);
void LedStatusHandler_SetPowerLed(void);
void LedStatusHandler_SetLedState(Hvac_FlapPosition_t pos);
void LedStatusHandler_IndicateError(void);
uint8_t LedStatusHandler_GetLedBits(void);
LedStatus_Mode_t LedStatusHandler_GetMode(void);

#ifdef __cplusplus
}
#endif

#endif /* LED_STATUS_HANDLER_H */
