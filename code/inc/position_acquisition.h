#ifndef POSITION_ACQUISITION_H
#define POSITION_ACQUISITION_H

#include <stdint.h>

// Position acquisition public API
int GetCurrentPosition(void);
void UpdatePosition(void);

#endif // POSITION_ACQUISITION_H
