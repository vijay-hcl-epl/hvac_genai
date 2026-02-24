#ifndef POSITION_FEEDBACK_READER_H
#define POSITION_FEEDBACK_READER_H

#include <stdint.h>
#include <stdbool.h>

void position_feedback_reader_init(void);
uint16_t get_position(void);
bool is_position_valid(uint16_t position);

#endif // POSITION_FEEDBACK_READER_H
