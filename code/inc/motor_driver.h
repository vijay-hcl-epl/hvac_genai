#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

typedef enum {
    DIR_CW = 0,
    DIR_CCW
} Direction;

void set_direction(Direction dir);
void enable_motor(void);
void disable_motor(void);

#endif // MOTOR_DRIVER_H
