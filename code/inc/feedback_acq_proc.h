#ifndef FEEDBACK_ACQ_PROC_H
#define FEEDBACK_ACQ_PROC_H
#include <stdint.h>
#include <stdbool.h>
void FBK_Acquire(void);
uint16_t FBK_GetRawADC(void);
uint8_t FBK_GetLogicalPosition(void);
bool FBK_IsValid(void);
#endif // FEEDBACK_ACQ_PROC_H
