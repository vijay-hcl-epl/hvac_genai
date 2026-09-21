#ifndef SYSTEM_STARTUP_INITIALIZATION_H
#define SYSTEM_STARTUP_INITIALIZATION_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Traces: SWE-REQ-020, SWE-REQ-021, SWE-REQ-036 */

void SystemStartupInitialization_SystemInit(void);
void SystemStartupInitialization_MainTask(void);
bool SystemStartupInitialization_IsInitialized(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STARTUP_INITIALIZATION_H */
