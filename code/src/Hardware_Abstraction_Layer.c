#include "Hardware_Abstraction_Layer.h"

void HardwareAbstractionLayer_Init(HalHandle_t* h) {
    for(int i=0; i<8; ++i) {
        h->handle_table[i]=0;
        h->logic_map[i]=0;
    }
}

int HardwareAbstractionLayer_Command(HalHandle_t* h, int logic_cmd) {
    // Translate, perform hardware action; dummy implementation
    return 0;
}
