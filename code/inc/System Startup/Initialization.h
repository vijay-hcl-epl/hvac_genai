#ifndef SYSTEM_STARTUP_INITIALIZATION_H
#define SYSTEM_STARTUP_INITIALIZATION_H

#include <stdbool.h>

void System_Startup_Initialization_Init(void);
bool System_Startup_Initialization_IsInitialized(void);
bool system_init(void);

#endif /* SYSTEM_STARTUP_INITIALIZATION_H */
