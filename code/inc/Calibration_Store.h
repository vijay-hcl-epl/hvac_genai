#ifndef CALIBRATION_STORE_H
#define CALIBRATION_STORE_H

typedef struct {
    int calibration_table[6];
} CalibrationStore_t;

void Calibration_Store_Init(CalibrationStore_t *cs);
int Calibration_Store_Get(CalibrationStore_t *cs, int idx);

#endif // CALIBRATION_STORE_H
