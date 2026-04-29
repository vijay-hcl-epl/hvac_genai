#ifndef FEEDBACK_ACQUISITION_H
#define FEEDBACK_ACQUISITION_H
#include <stdint.h>
#include <stdbool.h>

int feedback_acquire(uint8_t* pos_out, bool* valid_out);

#endif // FEEDBACK_ACQUISITION_H
