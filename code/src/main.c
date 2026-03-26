#include "system_init.h"
#include "user_command_if.h"
#include "flap_control.h"
#include "adc_if.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
int main(void)
{
    SystemInit_Init();
    while (1) {
        UserCommandIF_Process();
        FlapControl_Update();
        // ... add further polling/status ...
    }
    return 0;
}
