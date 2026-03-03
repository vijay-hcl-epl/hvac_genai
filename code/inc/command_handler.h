#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_FLAP_POS_MIN 0
#define CMD_FLAP_POS_MAX 5

typedef enum {
    CMD_VALID = 0,
    CMD_INVALID,
    CMD_OUT_OF_RANGE
} CMD_Status_t;

void CMD_Init(void);
CMD_Status_t CMD_ParseAndValidate(const uint8_t *input, uint8_t len);
int CMD_GetTargetPosition(void);
void CMD_Consume(void);
bool CMD_HasValidCommand(void);
void CMD_ClearError(void);

#endif // COMMAND_HANDLER_H
