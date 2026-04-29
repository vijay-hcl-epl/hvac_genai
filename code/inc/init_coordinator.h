#ifndef INIT_COORDINATOR_H
#define INIT_COORDINATOR_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SYS_STATE_INIT,
    SYS_STATE_IDLE,
    SYS_STATE_MOVING,
    SYS_STATE_INVALID_FEEDBACK
} SystemState;

typedef struct {
    SystemState state;
    uint8_t target_pos;
    uint8_t current_pos;
    bool position_valid;
} SystemStatus;

void system_init(void);
void main_loop(void);

#endif // INIT_COORDINATOR_H
