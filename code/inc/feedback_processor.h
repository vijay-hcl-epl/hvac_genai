#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

// API
void feedback_processor_init(void);
void feedback_processor_update(void);
uint8_t feedback_processor_get_position(bool *valid);

#endif // FEEDBACK_PROCESSOR_H
