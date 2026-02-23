#ifndef CONFIG_CONSTANTS_H
#define CONFIG_CONSTANTS_H

#include <stdint.h>

#define FLAP_POSITION_COUNT 6

typedef struct {
    uint16_t min;
    uint16_t max;
} position_thresholds_t;

const position_thresholds_t* config_get_pos_thresholds(void);
void config_init(void);

#endif // CONFIG_CONSTANTS_H
