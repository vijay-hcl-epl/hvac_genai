/**
 @file indication_manager.h
 @brief Control of Power and Position LEDs.
 @responsibility: Status/Position indicator management (SWE-REQ-016, -017) */
#ifndef INDICATION_MANAGER_H
#define INDICATION_MANAGER_H
#include <stdint.h>
#include <stdbool.h>
void IndicationManager_Init(void);
void IndicationManager_Update(bool system_power_on, uint8_t logical_position, bool pos_valid);
#endif /* INDICATION_MANAGER_H */
