#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
typedef enum { STATUS_OK = 0, STATUS_ERROR = 1 } Status_t;
void position_feedback_get(uint8_t *pos, Status_t *status);
void position_feedback_init(void);
#endif // POSITION_FEEDBACK_H
