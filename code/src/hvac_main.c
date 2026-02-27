#include "input_handler.h"
#include "control_logic.h"
#include "motor_driver.h"
#include "position_feedback.h"
#include "led_status.h"

// Example calibration (user-supplied in real use)
const PositionCalibration_t default_calib = {0, 4095, {500, 1000, 2000, 2800, 3500, 4095}};

void HVAC_Main(void)
{
    InputHandler_Init();
    MotorDriver_Init();
    PositionFeedback_Init(&default_calib);
    LEDStatus_Init();
    ControlLogic_Init(PositionFeedback_GetLogicalPosition());
    while (1) {
        // Poll ADC, UART elsewhere, then update modules with new data
        // e.g. InputHandler_UART_RxHandler() on UART RX elsewhere
        ControlLogic_Task();
    }
}
