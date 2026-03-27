#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

// Signal Interface States
typedef enum {
    STATE_SIGNAL_IDLE,
    STATE_SIGNAL_READ,
    STATE_SIGNAL_NORMALIZE,
    STATE_SIGNAL_ERROR
} SignalState_t;

// Signal Interface static data
static SignalState_t signal_state;
static int signal_raw_input;
static int signal_normalized_command;
static int signal_normalized_position;

// Function prototypes
void SignalInterface_Init(void);
int SignalInterface_ReadCommand(void);
int SignalInterface_ReadPosition(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
