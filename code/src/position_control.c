#include "position_control.h"
#include "motor_control.h"
#include "feedback_handling.h"
#include "led_indicate.h"

static int current_position = POS_FLAP_POS_MIN;
static int target_position = POS_FLAP_POS_MIN;
static bool command_active = false;
static POS_State_t pos_state = POS_STATE_IDLE;

void POS_Init(void) {
    current_position = POS_FLAP_POS_MIN;
    target_position = POS_FLAP_POS_MIN;
    command_active = false;
    pos_state = POS_STATE_IDLE;
}

void POS_SetTarget(int tgt) {
    // Clamp target to allowed range
    if (tgt < POS_FLAP_POS_MIN) tgt = POS_FLAP_POS_MIN;
    if (tgt > POS_FLAP_POS_MAX) tgt = POS_FLAP_POS_MAX;
    target_position = tgt;
    command_active = true;
    pos_state = POS_STATE_MOVEREQ;
}

void POS_Process(void) {
    // Decision logic for position movement
    if (!command_active) {
        MOTOR_Stop();
        LED_SetPosition(current_position);
        pos_state = POS_STATE_IDLE;
        return;
    }
    if (current_position < target_position) {
        MOTOR_SetDirection(MOTOR_DIR_OPEN);
        MOTOR_Enable(true);
    } else if (current_position > target_position) {
        MOTOR_SetDirection(MOTOR_DIR_CLOSE);
        MOTOR_Enable(true);
    } else {
        // At position
        MOTOR_Stop();
        LED_SetPosition(current_position);
        command_active = false;
        pos_state = POS_STATE_IDLE;
    }
}

void POS_OnFeedbackUpdate(int pos, bool valid) {
    if (valid) {
        current_position = pos;
        // Re-evaluate position on update
        POS_Process();
    } else {
        // Enter error state, stop motor, indicate safe idle
        MOTOR_Stop();
        LED_SetStatus(LED_STATUS_ERROR);
        pos_state = POS_STATE_ERROR;
        command_active = false;
    }
}

POS_State_t POS_GetState(void) {
    return pos_state;
}

int POS_GetCurrentPosition(void) {
    return current_position;
}
