#include "command_interface.h"
#include "position_feedback.h"
#include "flap_motor_control.h"
#include "status_indication.h"
#include "control_logic.h"
#include "calibration_data.h"
#include "error_handler.h"
int main(void) {
    CommandInterface_Init();
    PositionFeedback_Init();
    FlapMotorControl_Init();
    StatusIndication_Init();
    ControlLogic_Init();
    CalibrationData_Init();
    ErrorHandler_Init();
    while (1) {
        // Simulate ADC ISR call, UART RX, and feedback loop
        // (in real MCU, would be ISRs or peripheral callbacks)
        // e.g.: PositionFeedback_AdcInterruptHandler(read_adc());
        // e.g.: CommandInterface_UartRxHandler(get_uart());
        FlapMotorControl_Update();
        // ...
    }
    return 0;
}
