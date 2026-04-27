#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
#include <stdbool.h>

#define LOGICAL_POSITIONS 5

void position_feedback_init(void);
void position_feedback_poll(void);

#endif // POSITION_FEEDBACK_H
