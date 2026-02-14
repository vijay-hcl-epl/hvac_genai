#include "startup.h"
#include "uart_handler.h"
#include "flap_ctrl.h"
#include "motor_driver.h"
#include "adc_feedback.h"
#include "led_status.h"

void Startup_Sequence(void) {
    // Call initialization for each software unit
    UART_Handler_Init();
    ADCFbk_Init();
    MotorDriver_Init();
    LEDStatus_Init();
    FlapCtrl_Init();
}
