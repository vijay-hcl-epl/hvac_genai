#include "Electrical_Interface_Driver.h"

void ElectricalInterfaceDriver_Init(EidHandle_t* e) {
    for(int i=0;i<8;++i) {
        e->reg_table[i]=0;
        e->status_reg[i]=0;
    }
}

int ElectricalInterfaceDriver_Actuate(EidHandle_t* e, int pin, int val) {
    // Set/clear hardware pins
    if(pin<8) {
        e->reg_table[pin] = val;
        return 0;
    }
    return -1; // Error
}

int ElectricalInterfaceDriver_Read(EidHandle_t* e, int pin) {
    if(pin<8) {
        return e->status_reg[pin];
    }
    return -1; // Error
}
