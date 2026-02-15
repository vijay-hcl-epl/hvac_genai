#ifndef FLAPCTRL_H
#define FLAPCTRL_H
#include <stdint.h>
/* MISRA: Rule 20.10 – Include only standard headers that are required */
void FlapCtrl_Init(void);
void FlapCtrl_NewTargetCmd(uint8_t pos);
void FlapCtrl_MainLoop(void);
#endif /* MISRA: Rule 20.5 – Preprocessor #endif should have comment */
