// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf §4, §22 (Power, Operation)
#ifndef FLAP_CTRL_LOGIC_H
#define FLAP_CTRL_LOGIC_H
#include <stdint.h>
void FlapCtrl_MoveTo(uint8_t position);
void FlapCtrl_Abort(void);
void FlapCtrl_StatusQuery(void);
void FlapCtrl_Init(void);
#endif
