#ifndef CONFIG_STATE_MANAGER_H
#define CONFIG_STATE_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

#define FLAP_POS_MIN      0
#define FLAP_POS_MAX      5
#define FLAP_POS_INVALID  (-1)
#define NUM_FLAP_POSITIONS 6

void ConfigState_Init(void);
int8_t ConfigState_GetCurrentPos(void);
void ConfigState_SetCurrentPos(int8_t p);
uint8_t ConfigState_GetTargetPos(void);
void ConfigState_SetTargetPos(uint8_t p);
bool ConfigState_GetMoveActive(void);
void ConfigState_SetMoveActive(bool flag);
bool ConfigState_GetOutOfRangeFlag(void);
void ConfigState_SetOutOfRangeFlag(bool flag);

// Additional flag get/set functions as needed

#endif // CONFIG_STATE_MANAGER_H
