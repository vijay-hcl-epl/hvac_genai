#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

typedef enum {
    FLAP_STATE_INIT,
    FLAP_STATE_IDLE,
    FLAP_STATE_MOVING,
    FLAP_STATE_HOLD,
    FLAP_STATE_ERROR
} FlapState;

void flap_control_init(void);
void start_move(unsigned int requested_position);
void stop_motor(void);
void flap_control_main(void);
void signal_error(void);
bool flap_in_error(void);

#endif // FLAP_CONTROL_LOGIC_H
