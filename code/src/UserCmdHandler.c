#include "UserCmdHandler.h"
#include "FlapCtrl.h"
#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
void UserCmdHandler_Init(void) {
    // Initialization if needed
}
void UserCmdHandler_OnUartRx(uint8_t rx_value) {
    if (rx_value >= FLAP_POS_MIN && rx_value <= FLAP_POS_MAX) {
        FlapCtrl_NewTargetCmd(rx_value);
    }
    // else ignore invalid
}
