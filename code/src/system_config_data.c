#include "system_config_data.h"
static const config_data_t data = { { 1000, 2000, 3000, 4000 }, 4 };
const config_data_t* CNF_Get(void) { return &data; }