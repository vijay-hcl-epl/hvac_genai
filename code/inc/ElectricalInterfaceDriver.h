#ifndef ELECTRICALINTERFACEDRIVER_H
#define ELECTRICALINTERFACEDRIVER_H

typedef enum {
    ELEC_IDLE,
    ELEC_OP,
    ELEC_DONE
} ElecState_t;

typedef struct {
    int motor_status;
    int adc_status;
    int led_status;
    ElecState_t state;
} ElectricalInterfaceDriver_t;

void ElecDrv_Init(ElectricalInterfaceDriver_t* instance);
void ElecDrv_PerformIO(ElectricalInterfaceDriver_t* instance);

#endif // ELECTRICALINTERFACEDRIVER_H
