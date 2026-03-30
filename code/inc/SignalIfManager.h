#ifndef SIGNAL_IF_MANAGER_H
#define SIGNAL_IF_MANAGER_H
#include <stdint.h>
typedef enum {
    SIG_OK,
    SIG_ADC_OUT_OF_RANGE
} SignalStatus;
void SignalIfManager_Init(void);
uint8_t SignalIfManager_GetPosition(void);
SignalStatus SignalIfManager_Update(uint16_t adc_value);
void SignalIfManager_SetLED(uint8_t pos);
void SignalIfManager_StopMotor(void);
#endif // SIGNAL_IF_MANAGER_H
