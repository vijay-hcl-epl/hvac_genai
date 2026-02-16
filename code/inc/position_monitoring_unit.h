#ifndef POSITION_MONITORING_UNIT_H
#define POSITION_MONITORING_UNIT_H
#include <stdbool.h>

// Position Monitoring error
typedef enum {
    POSITION_OK,
    POSITION_OOR,
    POSITION_ERROR
} position_status_t;

void position_monitor_init(void);
// Returns mapped position, sets error flag if OOR
int get_current_position(void);
position_status_t get_position_status(void);

#endif
