#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

void feedback_processor_init(void);
void feedback_processor_update(void);
bool feedback_processor_get_position(uint8_t *position, bool *valid);

#endif // FEEDBACK_PROCESSOR_H
