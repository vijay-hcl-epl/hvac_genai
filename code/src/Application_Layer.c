#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"

static AL_State_t al_state = AL_IDLE;
static AL_UserCommand_t al_last_cmd;

void AL_Init(void) {
    al_state = AL_IDLE;
}

void AL_DispatchCommand(const AL_UserCommand_t* cmd) {
    if (cmd) {
        al_last_cmd = *cmd;
        al_state = AL_COMMAND_RECEIVED;
    }
}

void AL_Task(void) {
    switch(al_state) {
    case AL_IDLE:
        // Wait for command
        break;
    case AL_COMMAND_RECEIVED:
        if (al_last_cmd.target_position >= 0) {
            SIM_ProcessCommand(al_last_cmd.target_position);
            al_state = AL_PROCESSING;
        } else {
            // Reject malformed/out-of-bounds command
            al_state = AL_IDLE;
        }
        break;
    case AL_PROCESSING:
        // Poll Signal Manager, check completion (omitted: stub)
        // ...
        al_state = AL_DONE;
        break;
    case AL_DONE:
        // Done, reset
        al_state = AL_IDLE;
        break;
    }
}
