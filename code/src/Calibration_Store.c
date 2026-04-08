#include "Calibration_Store.h"

void Calibration_Store_Init(CalibrationStore_t *cs) {
    for (int i = 0; i < 6; ++i) {
        cs->calibration_table[i] = 100*i; // Example static values
    }
}

int Calibration_Store_Get(CalibrationStore_t *cs, int idx) {
    if(idx >= 0 && idx < 6) {
        return cs->calibration_table[idx];
    }
    return 0;
}
