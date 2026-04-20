#include "config_calib.h"
static const uint16_t position_thresholds[6] = {200, 400, 600, 800, 1000, 4095};
static const uint16_t max_pwm = 950;
uint16_t get_config_param(uint8_t id) {
    if (id == MAX_PWM_ID) return max_pwm;
    if (id >= THRESH_0_ID && id < THRESH_0_ID+6) return position_thresholds[id-THRESH_0_ID];
    return 0; // default safe
}
