#ifndef FLAP_CONTROL_COORDINATOR_H
#define FLAP_CONTROL_COORDINATOR_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DIR_CW,
    DIR_CCW
} direction_t;

void Process_Position_Request(uint8_t target);
void FlapControl_Feedback_Update(uint8_t feedback_position);
void FlapControl_Error_Handler(void);

#endif // FLAP_CONTROL_COORDINATOR_H
