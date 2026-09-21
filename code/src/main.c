#include "System Startup Initialization.h"

/* Main bare-metal entry point for STM32CubeIDE/HAL project.
 * System-level glue traces: SWE-REQ-020, SWE-REQ-022, SWE-REQ-023.
 */

int main(void)
{
    SystemStartupInitialization_SystemInit();

    while (1)
    {
        SystemStartupInitialization_MainTask();
    }
}
