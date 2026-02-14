#include "FlapCtrl.h"
#include "MotorDriver.h"
#include "PosFeedback.h"
#include "StatusIndication.h"
#include <stdbool.h>
static uint8_t target_pos = 0;
static uint8_t curr_pos = 0;
static bool move_active = false;
void FlapCtrl_Init(void) {
    curr_pos = PosFeedback_GetPosition();
    StatusIndication_PowerLed(true);
    StatusIndication_SetLed(curr_pos);
    move_active = false;
}
void FlapCtrl_NewTargetCmd(uint8_t pos) {
    if (pos == curr_pos) return;
    target_pos = pos;
    move_active = true;
    FlapCtrl_MainLoop(); // Optional immediate kickoff
}
void FlapCtrl_MainLoop(void) {
    if (!move_active) return;
    int8_t dir;
    curr_pos = PosFeedback_GetPosition();
    if (!PosFeedback_InRange()) {
        MotorDriver_SetMotor(0); // stop
        move_active = false;
        return;
    }
    if (target_pos > curr_pos) dir = 1;
    else if (target_pos < curr_pos) dir = -1;
    else {
        MotorDriver_SetMotor(0); // stop
        move_active = false;
        StatusIndication_SetLed(curr_pos);
        return;
    }
    MotorDriver_SetMotor(dir);
}
