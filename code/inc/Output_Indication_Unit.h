#ifndef OUTPUT_INDICATION_UNIT_H
#define OUTPUT_INDICATION_UNIT_H

#include <stdint.h>

typedef struct {
    uint8_t led_state;
    uint8_t power_up_flag;
    uint8_t last_flap_position;
} OutputIndicationUnitData;

typedef enum {
    OIU_WAIT_FOR_STATUS_SIGNAL = 0,
    OIU_ACTIVATE_STATUS_LED,
    OIU_MONITOR_FLAP_POSITION,
    OIU_UPDATE_POSITION_LED
} OutputIndicationUnitState;

void Output_Indication_Unit_resp_1(OutputIndicationUnitData* data, uint8_t flap_position);
void Output_Indication_Unit_resp_2(OutputIndicationUnitData* data);

#endif // OUTPUT_INDICATION_UNIT_H
