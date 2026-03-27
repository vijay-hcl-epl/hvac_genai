#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

// Electrical Interface Driver States
typedef enum {
    STATE_EID_IDLE,
    STATE_EID_READ,
    STATE_EID_WRITE,
    STATE_EID_ERROR
} EidState_t;

// Electrical Driver static data
static EidState_t eid_state;
static int eid_adc_sample_value;
static int eid_gpio_output_state;
static int eid_input_state;

// Function prototypes
void ElectricalDriver_Init(void);
int ElectricalDriver_ReadAdc(void);
int ElectricalDriver_ReadInput(void);
void ElectricalDriver_SetMotor(int direction);
void ElectricalDriver_StopMotor(void);
void ElectricalDriver_SetStatusLed(int led_id, int state);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
