#include "uart_command_handler.h"
#include "flap_control_logic.h"
#include "position_feedback.h"
#include "motor_control.h"
#include "led_handler.h"
#include "config_data_store.h"

int main(void) {
    ConfigDataStore_Init();
    UART_CommandHandler_Init();
    PositionFeedback_Init();
    MotorControl_Init();
    LEDHandler_Init();
    FlapControlLogic_Init();

    while (1) {
        // Typical main loop (demo, not RTOS, no actual delays here)
        PositionFeedback_Sample();
        FlapControlLogic_ExecCycle();
        // Normally, poll UART or handle interrupts elsewhere
    }
    return 0;
}
