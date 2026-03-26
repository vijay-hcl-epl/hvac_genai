#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <stdint.h>
void Configuration_Init(void);
const uint16_t* Configuration_GetThresholds(void);
#endif
