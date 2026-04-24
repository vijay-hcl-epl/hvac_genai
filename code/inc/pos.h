#ifndef POS_H
#define POS_H

#include <stdbool.h>
#include <stdint.h>

#define POS_POSITION_INVALID   (-1)
#define POS_POSITION_MIN      (0)
#define POS_POSITION_MAX      (5)

void pos_init(void);
void pos_periodic_sample(void);
bool pos_get_current_position(int *pos_value);
bool pos_get_valid_flag(void);

#endif // POS_H
