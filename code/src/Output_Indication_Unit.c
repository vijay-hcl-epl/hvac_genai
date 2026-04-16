#include "Output_Indication_Unit.h"

// Responsibility 1: Indicate system status and flap position using required LEDs.
void Output_Indication_Unit_resp_1(OutputIndicationUnitData* data, uint8_t flap_position) {
    // TRACE: "On status or flap position signal, update corresponding LED."
    data->led_state = flap_position; // Directly maps
    data->last_flap_position = flap_position;
}
// Responsibility 2: Illuminate status LED on power-up
void Output_Indication_Unit_resp_2(OutputIndicationUnitData* data) {
    data->power_up_flag = 1; // TRACE: "On power-up, turn ON status LED"
}
