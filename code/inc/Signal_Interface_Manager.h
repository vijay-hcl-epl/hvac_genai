#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#define SIM_MAX_POSITIONS 8

typedef enum {
    SIM_IDLE,
    SIM_MONITORING,
    SIM_COMMANDED,
    SIM_UPDATING
} SIM_State_t;

typedef enum {
    SIM_EVENT_NONE,
    SIM_ADC_CHANGE,
    SIM_COMMAND_RECEIVED,
    SIM_UPDATE_COMPLETE
} SIM_Event_t;

typedef struct {
    int adc_value;
    int flap_position;
} SIM_ADC_Status_t;

typedef struct {
    int buffer[16];
    int head;
    int tail;
} SIM_UART_Buffer_t;

void SIM_Init(void);
void SIM_ProcessADC(int adc_value);
void SIM_ProcessCommand(int target_position);
void SIM_Task(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
