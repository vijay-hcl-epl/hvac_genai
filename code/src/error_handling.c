#include "error_handling.h"
static error_code_t error_state = ERR_NONE;

void error_handling_init(void) {
    error_state = ERR_NONE;
}

void error_handling_set_error(error_code_t type) {
    error_state = type;
}

void error_handling_clear_error(void) {
    error_state = ERR_NONE;
}

error_code_t error_handling_get_state(void) {
    return error_state;
}
