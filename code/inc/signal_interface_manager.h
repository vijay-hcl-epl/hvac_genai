#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

typedef enum {
    SIG_STATE_IDLE,
    SIG_STATE_ACTIVE,
    SIG_STATE_WAIT_FOR_ACK,
    SIG_STATE_ERROR
} sig_state_t;

typedef struct {
    char command_queue[8][32];
    uint8_t queue_head;
    uint8_t queue_tail;
    uint8_t filter_flags;
    sig_state_t state;
} SignalInterfaceManager;

void sim_init(SignalInterfaceManager* sim);
void sim_receive_command(SignalInterfaceManager* sim, const char* cmd);
void sim_translate_and_forward(SignalInterfaceManager* sim);
void sim_validate_input(SignalInterfaceManager* sim);
void sim_handle_error(SignalInterfaceManager* sim);

#endif // SIGNAL_INTERFACE_MANAGER_H
