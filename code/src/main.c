#include "command_handler.h"
#include "flap_control.h"
#include "motor_control.h"
#include "feedback_adc.h"
#include "indication_led.h"
#include "static_config.h"
#include <stdint.h>
int main(void) {
    StaticConfig_Init();
    CommandHandler_Init();
    FlapControl_Init();
    MotorControl_Init();
    Feedback_Init();
    IndicationLed_Init();
    while(1) {
        /* Simulate UART receive (replace with actual HAL UART code) */
        /* uint8_t byte = UART_Read(); */
        /* CommandHandler_UartRxHandler(byte); */
        int cmd = CommandHandler_GetValidCommand();
        if (cmd != CMD_INVALID) {
            FlapControl_StartMovement((uint8_t)cmd);
        }
        FlapControl_PeriodicTask();
        Feedback_PeriodicTask();
    }
    return 0;
}
