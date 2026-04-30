#include "logical_mapper.h"

static const uint16_t supported_raw_values[FLAP_POS_COUNT] = {0, 128, 256, 512};
const FlapPosition_t supported_positions[FLAP_POS_COUNT] = {FLAP_POS_0, FLAP_POS_1, FLAP_POS_2, FLAP_POS_3};

int map_to_symbolic(uint16_t raw_val)
{
    for(int i = 0; i < FLAP_POS_COUNT; ++i) {
        if(raw_val == supported_raw_values[i])
            return (int)supported_positions[i];
    }
    return SYMBOLIC_INVALID;
}

const FlapPosition_t* get_supported_positions(void) {
    return supported_positions;
}

int map_error_status(void) {
    return SYMBOLIC_INVALID;
}
