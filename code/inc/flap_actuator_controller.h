#ifndef FLAP_ACTUATOR_CONTROLLER_H
#define FLAP_ACTUATOR_CONTROLLER_H
#include <stdbool.h>

// System state
typedef enum {
    CTRL_IDLE,
    CTRL_PROCESSING,
    CTRL_WAIT_MOVEMENT,
    CTRL_ERROR
} flap_ctrl_state_t;

void flap_actuator_controller_init(void);
void process_uart_command(int cmd);
void flap_actuator_controller_task(void); // To be called cyclically or from main loop
flap_ctrl_state_t get_flap_ctrl_state(void);
bool get_ctrl_error_flag(void);
void clear_ctrl_error(void);

#endif
