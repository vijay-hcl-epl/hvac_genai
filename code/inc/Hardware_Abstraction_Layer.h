#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

typedef enum {
    HAL_READY,
    HAL_AWAIT_REQUEST,
    HAL_EXECUTING,
    HAL_FAULT
} HAL_State_t;

typedef enum {
    HAL_EVENT_NONE,
    HAL_ACCESS_REQUEST,
    HAL_ACCESS_COMPLETE,
    HAL_ERROR_OCCURRED
} HAL_Event_t;

typedef struct {
    int gpio_table[8];
    int adc_table[8];
} HAL_AbstractionTables_t;

void HAL_Init(void);
void HAL_SetLED(int led, int state);
void HAL_SetMotor(int state);
int  HAL_ReadADC(int channel);

#endif // HARDWARE_ABSTRACTION_LAYER_H
