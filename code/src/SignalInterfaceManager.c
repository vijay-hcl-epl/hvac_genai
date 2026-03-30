#include "SignalInterfaceManager.h"
#include "HardwareAbstractionLayer.h"

void SignalIf_Init(SignalInterfaceManager_t* instance) {
    instance->cmd = -1;
    instance->routed_action = 0;
    instance->status_flag = 0;
    instance->state = FSM_IDLE;
}

void SignalIf_ReceiveCommand(SignalInterfaceManager_t* instance, int cmd) {
    instance->cmd = cmd;
    instance->state = FSM_PARSING;
}

void SignalIf_Run(SignalInterfaceManager_t* instance) {
    switch(instance->state) {
        case FSM_IDLE:
            // Wait for cmd
            break;
        case FSM_PARSING:
            // Map cmd to action
            if(instance->cmd >= 0 && instance->cmd <= 9) {
                instance->routed_action = instance->cmd; // Example mapping
                instance->state = FSM_DISPATCH;
            } else {
                instance->state = FSM_COMPLETE; // Discard/unmapped
            }
            break;
        case FSM_DISPATCH:
            // HardwareAbstractionLayer_ProcessAction(instance->routed_action);
            instance->state = FSM_COMPLETE;
            break;
        case FSM_COMPLETE:
            // Reset for next
            instance->cmd = -1;
            instance->state = FSM_IDLE;
            break;
        default:
            instance->state = FSM_IDLE;
            break;
    }
}
