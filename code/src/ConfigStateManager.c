/* ConfigStateManager.c - Implements Configuration & State Manager unit */
#include "ConfigStateManager.h"
static int8_t currPos = FLAP_POS_INVALID;
static uint8_t tgtPos = FLAP_POS_INVALID;
static bool moveActive = false;
static bool outOfRangeFlag = false;

void ConfigState_Init(void) {
    currPos = FLAP_POS_INVALID;
    tgtPos = FLAP_POS_INVALID;
    moveActive = false;
    outOfRangeFlag = false;
}

int8_t ConfigState_GetCurrentPos(void) {
    return currPos;
}
void ConfigState_SetCurrentPos(int8_t p) {
    currPos = p;
}
uint8_t ConfigState_GetTargetPos(void) {
    return tgtPos;
}
void ConfigState_SetTargetPos(uint8_t p) {
    tgtPos = p;
}
bool ConfigState_GetMoveActive(void) {
    return moveActive;
}
void ConfigState_SetMoveActive(bool flag) {
    moveActive = flag;
}
bool ConfigState_GetOutOfRangeFlag(void) {
    return outOfRangeFlag;
}
void ConfigState_SetOutOfRangeFlag(bool flag) {
    outOfRangeFlag = flag;
}
