#ifndef SYSTEM_STARTUP_INITIALIZATION_H
#define SYSTEM_STARTUP_INITIALIZATION_H

#include <stdint.h>

void SystemStartupInitialization_Init(void);
void SystemStartupInitialization_TaskDispatcher(void);
uint8_t SystemStartupInitialization_IsInitialized(void);

#endif /* SYSTEM_STARTUP_INITIALIZATION_H */
