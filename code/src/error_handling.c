#include "error_handling.h"
static uint8_t error_code = 0;
void error_handling_init(void) { error_code = 0; }
void error_handling_report(uint8_t code) { error_code = code; }
bool error_handling_has_error(void) { return error_code != 0; }
void error_handling_clear(void) { error_code = 0; }
