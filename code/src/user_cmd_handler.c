#include "user_cmd_handler.h"
#include <string.h>
static uint8_t target_pos = 0;
static bool new_cmd = false;
void CMDH_ProcessUART(void) { /* Placeholder for UART receive/parse */ }
uint8_t CMDH_GetTargetPosition(void) { return target_pos; }
bool CMDH_HasNewCommand(void) { return new_cmd; }