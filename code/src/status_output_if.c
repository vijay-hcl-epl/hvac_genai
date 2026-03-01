// RAG_SOURCE: infineon-tle9851qxw-datasheet-en.pdf §29.11, User Manual GPIO section
#include "status_output_if.h"
void StatusOutputIF_SetStatus(uint8_t state) {
    // Set GPIO (P0/P1 ALTSELx, DIR, DATA) per state to drive LED/status output
    // Use Px_ALTSEL0/1, Px_DIR, Px_DATA as per section GPIO/Port control
}
void StatusOutputIF_Init(void) {
    // Configure status output pin (see datasheet Table 14)
}
