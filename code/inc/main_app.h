#ifndef MAIN_APP_H
#define MAIN_APP_H

#include <stdint.h>
#include <stdbool.h>

/* System state enumeration */
typedef enum {
    SYS_STATE_INIT = 0,
    SYS_STATE_IDLE,
    SYS_STATE_MOVING,
    SYS_STATE_HOLDING,
    SYS_STATE_ERROR
} system_state_t;

void MainApp_Init(void);
void MainApp_Run(void);

#endif /* MAIN_APP_H */
