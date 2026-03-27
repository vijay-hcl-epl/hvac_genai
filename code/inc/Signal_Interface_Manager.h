#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

typedef enum {
    STATE_SIGNAL_IDLE,
    STATE_SIGNAL_READ,
    STATE_SIGNAL_NORMALIZE,
    STATE_SIGNAL_ERROR
} SignalManagerStateType;

typedef struct {
    int rawInputValue;
    int normalizedCommand;
    int normalizedPosition;
} SignalInterfaceManager_DataType;

int SignalInterface_ReadCommand(void);
int SignalInterface_ReadPosition(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
