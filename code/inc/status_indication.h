#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H
#include <stdint.h>
#include <stdbool.h>

void status_indication_init(void);
void status_indication_set_position(uint8_t pos);
void status_indication_set_error(bool err);

#endif // STATUS_INDICATION_H
