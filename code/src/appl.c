#include "appl.h"
#include "mc.h"
#include "fa.h"
#include "si.h"
static appl_state_t appl_state = APPL_IDLE;
static uint8_t curr_flap_pos = FLAP_POS_MIN;
static uint8_t target_flap_pos = FLAP_POS_MIN;
static uint8_t attempt_counter = 0;
#define MAX_ATTEMPTS 10
void appl_init(void) {
    appl_state = APPL_IDLE;
    curr_flap_pos = fa_get_pos();
    si_led_update(curr_flap_pos, true);
}
void appl_process_command(uint8_t cmd) {
    if (appl_state != APPL_IDLE) return;
    if (cmd < FLAP_POS_MIN || cmd > FLAP_POS_MAX) return;
    target_flap_pos = cmd;
    attempt_counter = 0;
    appl_state = APPL_MOVING;
    mc_move((target_flap_pos > curr_flap_pos) ? 1 : -1);
}
void appl_tick(void) {
    uint8_t pos = fa_get_pos();
    if (appl_state == APPL_MOVING) {
        attempt_counter++;
        if (fa_is_oor() || attempt_counter > MAX_ATTEMPTS) {
            mc_stop();
            appl_state = APPL_ERROR;
            si_led_update(curr_flap_pos, true);
            return;
        }
        if (pos == target_flap_pos) {
            mc_stop();
            curr_flap_pos = pos;
            appl_state = APPL_BUSY;
            si_led_update(curr_flap_pos, true);
            return;
        }
    } else if (appl_state == APPL_BUSY) {
        appl_state = APPL_IDLE;
    } else if (appl_state == APPL_ERROR) {
        // Wait for new command
    }
}
appl_state_t appl_get_state(void) {
    return appl_state;
}
