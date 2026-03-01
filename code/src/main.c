// RAG_SOURCE: All RAG topics (main software structure)
#include "user_command_if.h"
#include "flap_ctrl_logic.h"
#include "adc_if.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
#include "config_data.h"
#include "error_handler.h"
int main(void) {
    ConfigData_Load();
    UserCommandIF_Init();
    FlapCtrl_Init();
    ADC_IF_Init();
    MotorDriverIF_Init();
    StatusOutputIF_Init();
    ErrorHandler_Init();
    while (1) {
        // Poll/dispatch ISR-driven events
        // Call FlapCtrl_MoveTo/Abort as directed
        // Example: update ActualPos = ADC_IF_GetPos()
        // if (ActualPos == TargetPos) MotorDriverIF_Stop();
    }
    return 0;
}
