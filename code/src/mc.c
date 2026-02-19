#include "mc.h"
// Stub HW accessors
typedef struct {int dir_pin; int en_pin;} mc_output_conf_t;
static mc_state_t mc_state = MC_OFF;
void mc_init(void) {
    mc_state = MC_OFF;
}
void mc_move(int dir) {
    // Set HW pins here
    if (dir > 0)
        mc_state = MC_FWD;
    else if (dir < 0)
        mc_state = MC_REV;
    else
        mc_state = MC_OFF;
}
void mc_stop(void) {
    // Clear EN pin
    mc_state = MC_OFF;
}
mc_state_t mc_get_state(void) {
    return mc_state;
}
