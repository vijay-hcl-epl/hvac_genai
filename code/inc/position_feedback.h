#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*feedback_cb_t)(uint8_t position, bool in_range);
void position_feedback_init(feedback_cb_t cb);
void position_feedback_update(void);

#endif // POSITION_FEEDBACK_H
