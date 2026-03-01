#include "error_handling.h"
static bool error_state_flag = false;
void error_handling_init(void) { error_state_flag = false; }
void error_on_uart(void) { error_state_flag = true; }
void error_on_adc(void) { error_state_flag = true; }
bool error_is_safe(void) { return error_state_flag; }
void error_clear(void) { error_state_flag = false; }
