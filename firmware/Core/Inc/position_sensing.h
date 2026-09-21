#ifndef POSITION_SENSING_H
#define POSITION_SENSING_H

#include <stdint.h>

/* Use enum for constants instead of macros (MISRA 19.4, 6.1) */
enum { FLAP_POSITION_NUM = 6U };
enum { FLAP_POSITION_INVALID = 0xFFU };

/* Forward declaration of struct (MISRA 8.5) */
typedef struct PositionRange PositionRange_t;

extern void PositionSensing_Init(void);
extern void PositionSensing_Update(void);
extern uint8_t PositionSensing_GetPosition(uint8_t *pos_out);
extern uint8_t PositionSensing_IsValid(void);
extern uint8_t PositionSensing_IsAtTarget(uint8_t target);

#endif /* POSITION_SENSING_H */