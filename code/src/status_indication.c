#include "status_indication.h"
static status_code_t current_status = STATUS_IDLE;

void status_indication_init(void) {
    current_status = STATUS_IDLE;
}

void status_indication_set_status(status_code_t state) {
    current_status = state;
}

status_code_t status_indication_get_status(void) {
    return current_status;
}
