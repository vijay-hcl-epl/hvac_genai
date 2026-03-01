#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
void motor_driver_init(void);
void motor_move(int direction);
bool motor_is_active(void);
void motor_stop(void);
#endif // MOTOR_DRIVER_H
