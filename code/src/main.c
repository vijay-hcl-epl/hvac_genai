#include "ApplicationLayer.h"
#include "SignalIfManager.h"
#include "HAL.h"
int main(void)
{
    HAL_Init();
    SignalIfManager_Init();
    ApplicationLayer_Init();
    // Main deterministic loop
    while(1)
    {
        uint16_t adc = HAL_GetADC();
        if(SignalIfManager_Update(adc) == SIG_OK) {
            ApplicationLayer_Task();
        }
        // Example UART receive (polling)
        uint8_t command = HAL_UARTReceive();
        if(command <= 5U) {
            ApplicationLayer_OnCommand(command);
        }
    }
    return 0;
}
