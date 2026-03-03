#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H
#include <stdint.h>

void status_indication_init(void);
void status_indication_update(uint16_t position);

#endif // STATUS_INDICATION_H
