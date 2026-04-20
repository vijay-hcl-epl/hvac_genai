#ifndef CONFIG_DATA_STORE_H
#define CONFIG_DATA_STORE_H

#include <stdbool.h>

#define CONFIG_POSITIONS      6

void ConfigDataStore_Init(void);
int ConfigDataStore_GetPositionCount(void);
int ConfigDataStore_GetADCMin(int index);
int ConfigDataStore_GetADCMax(int index);
int Config_ADC_ReadRaw(void);
void ConfigDataStore_SetMotorDir(int dir); // 0=one direction, 1=reverse
void ConfigDataStore_SetMotorEnable(bool en);
void ConfigDataStore_SetLED(int index, int on);

#endif // CONFIG_DATA_STORE_H
