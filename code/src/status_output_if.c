#include "status_output_if.h"
static StatusCode status_code = STATUS_IDLE;
void StatusOutputIf_Init(void) {
    status_code = STATUS_IDLE;
}
void StatusOutputIf_SetStatus(StatusCode code) {
    status_code = code;
    // GPIO or high-side driver update stub
}
