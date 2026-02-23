#include "config_constants.h"

static const position_thresholds_t pos_thresholds[FLAP_POSITION_COUNT] =
{{0, 199}, {200, 399}, {400, 599}, {600, 799}, {800, 999}, {1000, 1200}};

const position_thresholds_t* config_get_pos_thresholds(void) { return pos_thresholds; }
void config_init(void) {}
