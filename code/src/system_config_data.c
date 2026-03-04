#include "system_config_data.h"
#include <stdint.h>

const uint16_t adc_thresholds[FLAP_POSITIONS+1] = {0, 800, 1600, 2400, 3200, 4000, 4096};
const uint8_t led_pin_map[FLAP_POSITIONS] = {0, 1, 2, 3, 4, 5};
