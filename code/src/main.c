#include "user_command_if.h"
#include "flap_control_logic.h"
#include "adc_interface.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
#include "config_data.h"
#include "error_handler.h"

int main(void) {
    UserCommandIF_Init();
    FlapControlLogic_Init();
    ADC_Interface_Init();
    MotorDriverIF_Init();
    StatusOutputIF_Init();
    ConfigData_Init();
    ErrorHandler_Init();
    while(1) {
        UserCommandIF_Process();
        FlapControlLogic_Update();
    }
    return 0;
}
