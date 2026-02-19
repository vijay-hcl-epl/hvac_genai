#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
#include <stdint.h>

typedef enum {
    ERR_NONE = 0,
    ERR_CMD_INVALID,
    ERR_POSITION_IMPLAUSIBLE,
    ERR_MOTOR_FAULT
} error_code_t;

void error_handling_init(void);
void error_handling_set_error(error_code_t type);
void error_handling_clear_error(void);
error_code_t error_handling_get_state(void);

#endif // ERROR_HANDLING_H
