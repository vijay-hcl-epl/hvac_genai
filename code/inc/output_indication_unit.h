#ifndef OUTPUT_INDICATION_UNIT_H
#define OUTPUT_INDICATION_UNIT_H

#include <stdint.h>

#define LED_FLAG_COUNT 8

// Internal Data Design
typedef struct {
    uint8_t led_status_flags[LED_FLAG_COUNT];
} OutputIndicationUnitData;

// State Machine
typedef enum {
    STATE_UPDATE_LEDS,
    STATE_ENFORCE_SINGLE_GREEN
} OutputIndicationUnitState;

// Function Declarations
void output_indication_unit_resp_0(OutputIndicationUnitData* data);
void output_indication_unit_resp_1(OutputIndicationUnitData* data);

#endif // OUTPUT_INDICATION_UNIT_H
