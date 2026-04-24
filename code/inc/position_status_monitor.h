#ifndef POSITION_STATUS_MONITOR_H
#define POSITION_STATUS_MONITOR_H

#include <stdbool.h>
#include <stdint.h>

#define POS_VALID_MIN 0
#define POS_VALID_MAX 100

typedef enum {
    POS_STATUS_NORMAL,
    POS_STATUS_OUT_OF_RANGE
} pos_status_t;

typedef struct {
    int  last_position;
    bool out_of_range;
} position_status_t;

void position_status_init(void);
int  position_status_get(void);
pos_status_t position_status_get_status(void);
void position_status_periodic_task(void);

#endif // POSITION_STATUS_MONITOR_H
