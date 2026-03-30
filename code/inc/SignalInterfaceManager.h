#ifndef SIGNALINTERFACEMANAGER_H
#define SIGNALINTERFACEMANAGER_H

typedef enum {
    FSM_IDLE,
    FSM_PARSING,
    FSM_DISPATCH,
    FSM_COMPLETE
} SigIfState_t;

typedef struct {
    int cmd;
    int routed_action;
    int status_flag;
    SigIfState_t state;
} SignalInterfaceManager_t;

void SignalIf_Init(SignalInterfaceManager_t* instance);
void SignalIf_Run(SignalInterfaceManager_t* instance);
void SignalIf_ReceiveCommand(SignalInterfaceManager_t* instance, int cmd);

#endif // SIGNALINTERFACEMANAGER_H
