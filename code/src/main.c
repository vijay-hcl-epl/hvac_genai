#include "Motor_Flap_Actuation_and_Positioning_Unit.h"
#include "Position_Sensing_and_Monitoring_Unit.h"
#include "System_Initialization_and_Safety_Unit.h"
#include "Input_Command_Handling_Unit.h"
#include "LED_Status_and_Feedback_Unit.h"

void system_init(void) {
    System_Initialization_and_Safety_Unit_resp_0();
}

int main(void) {
    system_init();
    while (1) {
        Input_Command_Handling_Unit_resp_0();
        Input_Command_Handling_Unit_resp_1();
        Position_Sensing_and_Monitoring_Unit_resp_0();
        Motor_Flap_Actuation_and_Positioning_Unit_resp_0();
        Motor_Flap_Actuation_and_Positioning_Unit_resp_1();
        Motor_Flap_Actuation_and_Positioning_Unit_resp_2();
        Motor_Flap_Actuation_and_Positioning_Unit_resp_3();
        Motor_Flap_Actuation_and_Positioning_Unit_resp_4();
        System_Initialization_and_Safety_Unit_resp_1();
        LED_Status_and_Feedback_Unit_resp_0();
        LED_Status_and_Feedback_Unit_resp_1();
    }
    return 0;
}
