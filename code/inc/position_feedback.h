#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
#include <stdbool.h>

void position_feedback_init(void);
uint16_t position_feedback_get_position(void);
bool position_feedback_is_plausible(void);

#endif // POSITION_FEEDBACK_H
