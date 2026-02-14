#ifndef FLAPCTRL_H
#define FLAPCTRL_H
#include <stdint.h>
void FlapCtrl_Init(void);
void FlapCtrl_NewTargetCmd(uint8_t pos);
void FlapCtrl_MainLoop(void);
#endif // FLAPCTRL_H
