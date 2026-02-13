#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

#define FLAP_POSITION_COUNT 6
#define FLAP_POSITION_INVALID -1

void feedback_processor_init(void);
int8_t feedback_get_position(void);

#endif // FEEDBACK_PROCESSOR_H
/* MISRA: Rule 20.3 – Ending preprocessor directives with comments for readability */
