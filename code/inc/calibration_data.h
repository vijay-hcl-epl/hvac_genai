#ifndef CALIBRATION_DATA_H
#define CALIBRATION_DATA_H
#include <stdint.h>
uint8_t MapAdcToPosition(uint16_t adc_value);
void CalibrationData_Init(void);
#endif // CALIBRATION_DATA_H
