#include "user_cmd_handler.h"
#include "position_ctrl_logic.h"
#include "motor_control.h"
#include "feedback_acq_proc.h"
#include "status_led_indication.h"
#include "system_config_data.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    StatusLED_ShowPower(true);
    FeedbackAcq_Trigger();
    while(1) {
        uint8_t rx_byte;
        // Example: simulate UART rx
        printf("Enter cmd (0-4): ");
        if (scanf("%hhu", &rx_byte) == 1) {
            UserCmdHandler_Process(rx_byte);
        }
        FeedbackAcq_Trigger();
        PositionCtrl_Update();
        StatusLED_Set(PositionCtrl_GetStatus());
    }
    return 0;
}
