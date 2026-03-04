#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H
#include <stdbool.h>
#include "SystemTypes.h"

void StatusIndicator_Update(enum FlapPosition pos, bool powerOn);

#endif // STATUS_INDICATOR_H
