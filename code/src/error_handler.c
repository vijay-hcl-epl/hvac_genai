#include "error_handler.h"
#include "status_indication.h"
#include "state_machine.h"
void IErrorHandler_notify(uint8_t code, int src) {
    IStatusUpdate_set(STATUS_FAULT);
}
