#ifndef SENSING_H
#define SENSING_H
#include <stdint.h>
#include <stdbool.h>

void SENS_Init(void);
bool SENS_GetCurrentPosition(int *out_position);
void SENS_PeriodicSample(void);

#endif // SENSING_H
