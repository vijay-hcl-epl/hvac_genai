#include "system_init.h"
#include "user_command_if.h"
#include "flap_control.h"
#include "adc_if.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
#include "configuration.h"
#include "error_handler.h"
void SystemInit_Init(void) {
    Configuration_Init();
    ErrorHandler_Init();
    AdcIf_Init();
    MotorDriver_Init();
    StatusOutputIf_Init();
    UserCommandIF_Init();
    FlapControl_Init();
}
