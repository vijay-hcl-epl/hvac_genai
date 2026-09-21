#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

#define FEEDBACK_PROCESSOR_POSITION_COUNT (4U)
#define FEEDBACK_PROCESSOR_POSITION_MIN   (0U)
#define FEEDBACK_PROCESSOR_POSITION_MAX   (3U)

typedef struct
{
    uint8_t position;
    uint8_t valid;
} FeedbackProcessor_PositionType;

void FeedbackProcessor_Init(void);
void FeedbackProcessor_Update(void);
FeedbackProcessor_PositionType FeedbackProcessor_GetPosition(void);
uint16_t FeedbackProcessor_GetAdcRaw(void);

#endif /* FEEDBACK_PROCESSOR_H */
