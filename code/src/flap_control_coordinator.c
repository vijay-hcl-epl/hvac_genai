#include "flap_control_coordinator.h"
#include "motor_control.h"
#include "feedback_processing.h"
#include "led_management.h"

static uint8_t target_position = 0;
static uint8_t current_position = 0;
static bool move_in_progress = false;
static bool error_state = false;

void Process_Position_Request(uint8_t target) {
    if (move_in_progress || error_state) return;
    if (target > 5) return;
    if (target == current_position) return;
    target_position = target;
    move_in_progress = true;
    direction_t dir = (target_position > current_position) ? DIR_CW : DIR_CCW;
    Enable_Motor(dir);
}

void FlapControl_Feedback_Update(uint8_t feedback_position) {
    current_position = feedback_position;
    if (move_in_progress && current_position == target_position) {
        Disable_Motor();
        move_in_progress = false;
        Set_Position_LED(current_position);
        CommandManager_Complete();
    }
}

void FlapControl_Error_Handler(void) {
    Disable_Motor();
    error_state = true;
    move_in_progress = false;
}

// For simulation, add a reset function (not called by main.c)
void FlapControl_Reset_Error(void) {
    error_state = false;
}
