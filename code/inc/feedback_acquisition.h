#ifndef FEEDBACK_ACQUISITION_H
#define FEEDBACK_ACQUISITION_H

#include <stdint.h>

#define POSITION_INVALID   -1
#define POSITION_MIN      0
#define POSITION_MAX      5

int get_current_position(void);

#endif // FEEDBACK_ACQUISITION_H
