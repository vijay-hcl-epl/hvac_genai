#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdbool.h>
#include <stdint.h>
#include "Feedback Processor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Traces: SWE-REQ-001, SWE-REQ-002, SWE-REQ-003, SWE-REQ-015, SWE-REQ-022, SWE-REQ-036, SWE-REQ-038 */

typedef enum
{
    COMMAND_PARSER_STATE_INIT = 0,
    COMMAND_PARSER_STATE_WAIT_RX,
    COMMAND_PARSER_STATE_VALID,
    COMMAND_PARSER_STATE_INVALID
} CommandParser_State_t;

typedef struct
{
    bool valid;
    Hvac_FlapPosition_t position;
    uint8_t raw_byte;
} CommandParser_Command_t;

void CommandParser_Init(void);
void CommandParser_Task(void);
CommandParser_Command_t CommandParser_GetLatestCommand(void);
void CommandParser_ClearLatestCommand(void);
CommandParser_State_t CommandParser_GetState(void);

#ifdef __cplusplus
}
#endif

#endif /* COMMAND_PARSER_H */
