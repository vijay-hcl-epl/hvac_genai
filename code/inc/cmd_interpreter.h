#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H
#include <stdint.h>

int Cmd_decode(const uint8_t* rx, uint8_t* pos_val);
uint8_t Cmd_status(void);

#endif // CMD_INTERPRETER_H
