#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

typedef enum {
    SIGNAL_STATE_IDLE,
    SIGNAL_STATE_READ,
    SIGNAL_STATE_NORMALIZE,
    SIGNAL_STATE_ERROR
} SignalState_t;

typedef struct {
    int rawInputValue;
    int normalizedCommand;
    int normalizedPosition;
} SignalInterface_Data_t;

int SignalInterface_ReadCommand(void);
int SignalInterface_ReadPosition(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
