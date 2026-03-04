#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdbool.h>
#include "SystemTypes.h"

void FlapControlLogic_OnCommand(enum FlapPosition target);
void FlapControlLogic_OnFeedback(enum FlapPosition position);

#endif // FLAP_CONTROL_LOGIC_H
