#ifndef FLAP_POSITION_COMMAND_PROCESSOR_H
#define FLAP_POSITION_COMMAND_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

#define COMMAND_OK            0
#define COMMAND_OUT_OF_RANGE  1
#define COMMAND_INVALID       2

uint8_t process_command(uint16_t cmd);
uint8_t get_last_error(void);
void set_target_position(uint16_t pos);

#endif // FLAP_POSITION_COMMAND_PROCESSOR_H
