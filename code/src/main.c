#include "user_command_if.h"
#include "flap_control_logic.h"
#include "adc_interface.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
#include "error_handler.h"
#include "config_data.h"

int main(void)
{
    // System Initialization
    ErrorHandler_Init();
    ConfigData_Get();
    UserCommandIF_Init();
    FlapControlLogic_Init();
    ADCInterface_Init();
    MotorDriverIF_Init();
    StatusOutputIF_Init();

    while(1) {
        ADCInterface_StartConversion();
        FlapControlLogic_Process();
        UserCommandIF_Process();
        // Add delay or WFI as needed
    }

    return 0;
}
