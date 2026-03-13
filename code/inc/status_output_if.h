#ifndef STATUS_OUTPUT_IF_H
#define STATUS_OUTPUT_IF_H

#include <stdint.h>

typedef enum {
    STATUS_IDLE = 0,
    STATUS_OK,
    STATUS_MOVING,
    STATUS_ERROR
} StatusCode_t;

void StatusOutputIF_Init(void);
void StatusOutputIF_Set(StatusCode_t code);

#endif // STATUS_OUTPUT_IF_H
