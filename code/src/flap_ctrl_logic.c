// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf §4, §22
#include "flap_ctrl_logic.h"
#include "adc_if.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
#include "error_handler.h"
static uint8_t TargetPos = 0, ActualPos = 0, State = 0;
void FlapCtrl_Init(void) {
    TargetPos = 0; ActualPos = ADC_IF_GetPos(); State = 0;
}
void FlapCtrl_MoveTo(uint8_t position) {
    if (position > 5) { ErrorHandler_FlagError(0x02); return; }
    TargetPos = position;
    ActualPos = ADC_IF_GetPos();
    if (TargetPos == ActualPos) return;
    if (TargetPos > ActualPos)
        MotorDriverIF_Run(1, 80); // 1=forward, 80%=speed
    else MotorDriverIF_Run(0, 80); // 0=reverse
    State = 1;
}
void FlapCtrl_Abort(void) { MotorDriverIF_Stop(); State = 0; }
void FlapCtrl_StatusQuery(void) { StatusOutputIF_SetStatus(State); }
// Movement complete polling is expected in main loop
