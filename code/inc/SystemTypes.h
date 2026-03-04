#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H
#include <stdint.h>
#include <stdbool.h>

enum FlapPosition {
    FLAP_POS_INVALID = -1,
    FLAP_POS_0 = 0,
    FLAP_POS_1,
    FLAP_POS_2,
    FLAP_POS_3,
    FLAP_POS_4,
    FLAP_POS_MAX
};

enum MotorDirection {
    MOTOR_DIR_STOP = 0,
    MOTOR_DIR_FORWARD,
    MOTOR_DIR_REVERSE
};

enum ErrorType {
    ERROR_NONE = 0,
    ERROR_INVALID_COMMAND,
    ERROR_INVALID_FEEDBACK,
    ERROR_UNEXPECTED_STATE
};

#endif // SYSTEM_TYPES_H
