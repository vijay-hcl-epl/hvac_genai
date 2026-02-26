#include "config_manager.h"
// Example fake default config table
static ConfigTable flash_sim = {{300, 600, 900, 1200, 1500, 1800}, 20000, 0x01, 0x01};
int IFlashConfig_get(ConfigTable* ctable) {
    if (!ctable) return -1;
    *ctable = flash_sim;
    return 0;
}
