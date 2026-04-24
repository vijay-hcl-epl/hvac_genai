#include "supv.h"
#include <stdbool.h>

static bool cmdh_ready=false, pos_ready=false, mtr_ready=false, led_ready=false;
static bool init_complete=false;
static bool safe_state=false;

void supv_init(void) {
    cmdh_ready = pos_ready = mtr_ready = led_ready = false;
    init_complete = false;
    safe_state = false;
}

bool supv_get_init_complete(void) {
    return init_complete;
}

bool supv_get_safe_state(void) {
    return safe_state;
}

void supv_report_unit_status(bool c, bool p, bool m, bool l) {
    cmdh_ready=c; pos_ready=p; mtr_ready=m; led_ready=l;
    init_complete = cmdh_ready && pos_ready && mtr_ready && led_ready;
}

void supv_report_unit_error(const char *unit, int errcode) {
    (void)unit; (void)errcode;
    safe_state = true;
    // In real system: log error, halt/notify
}
