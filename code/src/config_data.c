// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf §4, NVM/Flash SDL
#include "config_data.h"
static ConfigData cfg;
void ConfigData_Load(void) {
    // Read block from Flash/NVM into cfg struct
}
ConfigData* ConfigData_Get(void) { return &cfg; }
