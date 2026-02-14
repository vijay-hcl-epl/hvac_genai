#include "flap_ctrl.h"
#include "uart_handler.h"
#include "adc_feedback.h"
#include "motor_driver.h"
#include "led_status.h"
static uint8_t target_pos = 0;
static bool action_active = false;
static bool error_state = false;
void FlapCtrl_Init(void) {
    target_pos = 0;
    action_active = false;
    error_state = false;
}
void Flap_Ctrl_Tick(void) {
    uint8_t current_pos = 0;
    bool adc_error = false;
    uint8_t cmd_val = 0;
    bool cmd_ok = false;
    UART_GetCommand(&cmd_val, &cmd_ok);
    ADCFbk_GetPosition(&current_pos, &adc_error);
    if (error_state) {
        LED_SetError();
        Motor_Drive_Stop();
        return;
    }
    if (cmd_ok && cmd_val != current_pos) {
        target_pos = cmd_val;
        action_active = true;
    }
    if (adc_error) {
        error_state = true;
        LED_SetError();
        Motor_Drive_Stop();
        return;
    }
    if (action_active) {
        if (current_pos < target_pos) {
            Motor_Drive_Set(1, 128); // 1 = forward; 128 = example PWM
        } else if (current_pos > target_pos) {
            Motor_Drive_Set(0, 128); // 0 = reverse
        } else {
            Motor_Drive_Stop();
            action_active = false;
        }
    }
    LED_SetStatus(current_pos);
}
