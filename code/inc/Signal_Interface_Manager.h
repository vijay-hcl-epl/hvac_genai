#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

// State Machine
typedef enum {
    SIM_IDLE,
    SIM_PARSE_UART,
    SIM_VALIDATE,
    SIM_RELAY_COMMAND
} SignalIfState_t;

// UART parser/command verification buffer
#define SIM_CMD_BUF_SIZE 1
typedef struct {
    uint8_t buf[SIM_CMD_BUF_SIZE];
    bool valid;
    SignalIfState_t state;
} SignalInterfaceManager_Data_t;

void SignalInterfaceManager_Init(SignalInterfaceManager_Data_t *data);
void SignalInterfaceManager_UARTInterrupt(SignalInterfaceManager_Data_t *data, uint8_t rx);
bool SignalInterfaceManager_ValidateCommand(uint8_t cmd);
void SignalInterfaceManager_RelayCommand(uint8_t cmd);

#endif // SIGNAL_INTERFACE_MANAGER_H
