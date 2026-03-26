#ifndef STATUS_OUTPUT_IF_H
#define STATUS_OUTPUT_IF_H
#include <stdint.h>
typedef enum { STATUS_OK, STATUS_ERR, STATUS_IN_MOTION, STATUS_IDLE, STATUS_TARGET_REACHED } StatusCode;
void StatusOutputIf_Init(void);
void StatusOutputIf_SetStatus(StatusCode code);
#endif
