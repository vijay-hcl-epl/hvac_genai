#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#include <stdint.h>

// Command Queue Size
#define CMD_QUEUE_SIZE 8

typedef enum {
    SIG_STATE_WAIT,
    SIG_STATE_PROCESSING,
    SIG_STATE_FEEDBACK,
    SIG_STATE_COMPLETE,
    SIG_STATE_ERR
} SignalState_t;

typedef struct {
    uint8_t cmd_queue[CMD_QUEUE_SIZE];
    uint8_t queue_head;
    uint8_t queue_tail;
    SignalState_t state;
    uint8_t current_position;
} SignalInterfaceManager_t;

void SignalInterfaceManager_Init(SignalInterfaceManager_t *ctx);
void SignalInterfaceManager_Task(SignalInterfaceManager_t *ctx);
void SignalInterfaceManager_CommandFlap(uint8_t position);

#endif // SIGNAL_INTERFACE_MANAGER_H
