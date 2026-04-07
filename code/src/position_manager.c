#include "position_manager.h"
#include "flap_control.h"
#include "position_feedback.h"
#define NUM_POSITIONS 6
static const uint16_t PositionTable[NUM_POSITIONS] = {100, 500, 1000, 1500, 2000, 2500};
static uint8_t CurrentPosition = 0;
static uint8_t TargetPosition = 0;
static uint8_t isBusy = 0;
PosMgrStatus_t PositionManager_command(uint8_t pos) {
    if (isBusy || pos >= NUM_POSITIONS) return POSMGR_BUSY;
    TargetPosition = pos;
    isBusy = 1;
    FlapControl_request(TargetPosition);
    return POSMGR_ACCEPTED;
}
uint8_t get_CurrentPosition(void) {
    return CurrentPosition;
}
void position_manager_init(void) {
    CurrentPosition = 0;
    TargetPosition = 0;
    isBusy = 0;
}
// Called by Position Feedback
void PositionManager_update(uint8_t actual) {
    CurrentPosition = actual;
    isBusy = 0;
}
