#ifndef FEEDBACK_ACQ_H
#define FEEDBACK_ACQ_H
#include <stdint.h>

#define FLAP_POS_INVALID 255
#define FLAP_POS_MAX 5

// Acquire flap position [0:5] or FLAP_POS_INVALID if out of range
uint8_t get_flap_position(void);

#endif // FEEDBACK_ACQ_H
