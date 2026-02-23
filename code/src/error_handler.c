#include "error_handler.h"
#include "flap_motor_control.h"
#include "status_indication.h"
static uint8_t error_flag = 0;
void ErrorHandler_Init(void) { error_flag = 0; }
void ErrorHandler_SetErrorState(uint8_t flag) {
    error_flag = flag;
    FlapMotorControl_Stop();
    StatusIndication_SetPositionLED(0xFF);
}
void ErrorHandler_ClearErrorState(void) { error_flag = 0; }
