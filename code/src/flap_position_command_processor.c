#include "flap_position_command_processor.h"
#include "logical_mapper.h"

static uint16_t current_position = 0;
static uint8_t last_error = COMMAND_OK;

uint8_t process_command(uint16_t cmd)
{
    int symbolic = map_to_symbolic(cmd);
    if(symbolic < 0) {
        last_error = COMMAND_OUT_OF_RANGE;
        return COMMAND_OUT_OF_RANGE;
    }
    set_target_position((uint16_t)symbolic);
    last_error = COMMAND_OK;
    return COMMAND_OK;
}

uint8_t get_last_error(void) {
    return last_error;
}

void set_target_position(uint16_t pos) {
    // TODO: issue position update command to application
    current_position = pos;
}
