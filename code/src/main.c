#include "system_init_platform.h"
#include "command_interpreter.h"
#include "position_controller.h"
#include "motor_actuator.h"
#include "feedback_processor.h"
#include "indicator_manager.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    SystemInit_All();
    CommandInterpreter_Init();
    MotorActuator_Init();
    FeedbackProcessor_Init();
    IndicatorManager_Init();
    PositionController_Init();

    char rx_buffer[8] = {0};
    uint8_t valid_cmd = 0;
    while (1) {
        // Simulate UART RX buffer read (replace with actual UART mechanism in MCU code)
        fgets(rx_buffer, sizeof(rx_buffer), stdin); // Stand-in: read from stdin for demo
        if (CommandInterpreter_Validate(rx_buffer, &valid_cmd)) {
            if (PositionController_RequestMove(valid_cmd)) {
                // Movement started, main loop will process
            }
        }
        PositionController_MainLoop();
    }
    return 0;
}
