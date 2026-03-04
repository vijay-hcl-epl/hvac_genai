#include "system_config_data.h"

static const struct pos_map_entry mapping_table[8] = {
    { 100, 0 },
    { 500, 1 },
    { 900, 2 },
    { 1300, 3 },
    { 1700, 4 },
    { 2100, 5 },
    { 2500, 6 },
    { 4095, 7 }
};

static int calibration_const = 42;
static int config_limits[2] = {0, 7};

const struct pos_map_entry* config_get_mapping(void) {
    return mapping_table;
}

int config_get_calibration(void) {
    return calibration_const;
}

int config_get_limit(int type) {
    if(type >= 0 && type < 2) {
        return config_limits[type];
    }
    return -1;
}
