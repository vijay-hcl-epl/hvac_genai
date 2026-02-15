#include "UserCmdHandler.h"
#include "FlapCtrl.h"
#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
void UserCmdHandler_Init(void) {
    /* MISRA: Rule 2.2 – Empty function body should have a comment */
    /* Initialization if needed */
}
void UserCmdHandler_OnUartRx(uint8_t rx_value) {
    if ((rx_value >= FLAP_POS_MIN) && (rx_value <= FLAP_POS_MAX)) { /* MISRA: Rule 12.1 – Enclose complex expressions in parentheses */
        FlapCtrl_NewTargetCmd(rx_value);
    }
    else {
        /* MISRA: Rule 14.2 – Else after if should be on same level*/
        /* else ignore invalid */
    }
}
