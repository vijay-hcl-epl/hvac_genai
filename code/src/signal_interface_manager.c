#include "signal_interface_manager.h"
#include <string.h>

void sim_init(SignalInterfaceManager* sim) {
    memset(sim->command_queue, 0, sizeof(sim->command_queue));
    sim->queue_head = 0;
    sim->queue_tail = 0;
    sim->filter_flags = 0;
    sim->state = SIG_STATE_IDLE;
}

void sim_receive_command(SignalInterfaceManager* sim, const char* cmd) {
    if ((sim->queue_tail + 1) % 8 != sim->queue_head) {
        strncpy(sim->command_queue[sim->queue_tail], cmd, 31);
        sim->command_queue[sim->queue_tail][31] = '\0';
        sim->queue_tail = (sim->queue_tail + 1) % 8;
        sim->state = SIG_STATE_ACTIVE;
    } else {
        sim->state = SIG_STATE_ERROR;
    }
}

void sim_translate_and_forward(SignalInterfaceManager* sim) {
    if (sim->queue_head != sim->queue_tail) {
        // Simulate translation
        sim->queue_head = (sim->queue_head + 1) % 8;
        sim->state = SIG_STATE_WAIT_FOR_ACK;
    }
}

void sim_validate_input(SignalInterfaceManager* sim) {
    // Basic validation
    if (sim->filter_flags) {
        sim->state = SIG_STATE_ERROR;
    }
}

void sim_handle_error(SignalInterfaceManager* sim) {
    // Handle error, flush queue
    sim->queue_head = sim->queue_tail;
    sim->state = SIG_STATE_IDLE;
}
