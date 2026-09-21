#ifndef SYSTEM_STARTUP_INITIALIZATION_H
#define SYSTEM_STARTUP_INITIALIZATION_H

#include <stdint.h>

void SystemStartup_Init(void);
void SystemStartup_TaskDispatcher(void);
uint8_t SystemStartup_IsInitialized(void);

#endif /* SYSTEM_STARTUP_INITIALIZATION_H */
