#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H
#include <stdint.h>

typedef enum {
    STATUS_IDLE = 0,
    STATUS_MOVING,
    STATUS_REACHED,
    STATUS_ERROR
} status_code_t;

void status_indication_init(void);
void status_indication_set_status(status_code_t state);
status_code_t status_indication_get_status(void);

#endif // STATUS_INDICATION_H
