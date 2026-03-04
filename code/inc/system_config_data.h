#ifndef SYSTEM_CONFIG_DATA_H
#define SYSTEM_CONFIG_DATA_H

#include <stdint.h>

struct pos_map_entry {
    uint16_t adc_val;
    int logic_pos;
};

/** Returns pointer to mapping table */
const struct pos_map_entry* config_get_mapping(void);

/** Returns calibration constant(s) */
int config_get_calibration(void);

/** Returns limit value by type. */
int config_get_limit(int type);

#endif // SYSTEM_CONFIG_DATA_H
