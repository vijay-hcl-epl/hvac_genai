#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>
#define NUM_POSITIONS 5

bool Config_IsValidPosition(uint8_t pos);
bool Config_MapADCToPosition(uint16_t adc, uint8_t* pos_idx);
uint8_t Config_GetNumPositions(void);
uint8_t Config_GetDefaultPWMDuty(void);

#endif // CONFIG_H
