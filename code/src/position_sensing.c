#include "position_sensing.h"
#include "config_constants.h"
#include "hw_abstraction.h"

static uint8_t last_logical_position = POSITION_INVALID;

void position_sensing_init(void)
{
    last_logical_position = POSITION_INVALID;
}

uint8_t position_sensing_get_current_position(void)
{
    return last_logical_position;
}

bool position_sensing_is_valid_position(uint8_t logical_pos)
{
    return (logical_pos >= FLAP_POSITION_MIN && logical_pos <= FLAP_POSITION_MAX);
}

void position_sensing_periodic(void)
{
    uint16_t adc_val = hw_adc_read();
    const position_thresholds_t *tbl = config_get_pos_thresholds();
    last_logical_position = POSITION_INVALID;
    for (uint8_t p = FLAP_POSITION_MIN; p <= FLAP_POSITION_MAX; ++p)
    {
        if (adc_val >= tbl[p].min && adc_val <= tbl[p].max) {
            last_logical_position = p;
            break;
        }
    }
}
