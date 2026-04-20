#ifndef FEEDBACK_ACQ_H
#define FEEDBACK_ACQ_H
#include <stdint.h>
#include <stdbool.h>
void update_feedback(void);
uint8_t get_feedback(void);
bool is_feedback_valid(void);
#endif // FEEDBACK_ACQ_H
