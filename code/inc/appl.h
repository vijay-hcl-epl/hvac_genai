#ifndef APPL_H_
#define APPL_H_
#include <stdint.h>
#include <stdbool.h>
// Application state
typedef enum { APPL_IDLE, APPL_MOVING, APPL_BUSY, APPL_ERROR } appl_state_t;
void appl_init(void);
void appl_tick(void);
void appl_process_command(uint8_t cmd);
appl_state_t appl_get_state(void);
#endif
