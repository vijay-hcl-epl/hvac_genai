/**
 @file flap_control.h
 @brief Implements flap actuator closed-loop logic and motor commands.
 @responsibility:
 Compares target vs. current position (SWE-REQ-005..007, -011)
 Commands Hardware Abstraction for motor movement
 Stops on error or out-of-range */
#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H
#include <stdint.h>
#include <stdbool.h>

/* Initialization */
void FlapControl_Init(void);

/* Primary processing function: runs closed-loop control each main loop */
void FlapControl_Process(uint8_t target_position, uint8_t current_position, bool position_valid);

/* Returns true if flap at target position */
bool FlapControl_IsPositionReached(void);

#endif /* FLAP_CONTROL_H */
