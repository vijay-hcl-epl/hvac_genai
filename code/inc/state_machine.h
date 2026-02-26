#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
typedef enum { IDLE, MOVING, TARGET, FAULT, STOP } FlapState;
void IStateMachine_run(void);
#endif
