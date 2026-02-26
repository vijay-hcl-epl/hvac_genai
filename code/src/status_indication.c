// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf High-Side Switch, 26.4.1 p.1450+
#include "status_indication.h"
#include "error_handler.h"
#define HS_CTRL (*(volatile unsigned int*)0x40015004)
void IStatusUpdate_set(StatusType t) {
    if (t == STATUS_POSITION)
        HS_CTRL |= (1 << 0); // HS1_EN enable
    else if (t == STATUS_FAULT)
        HS_CTRL &= ~(1 << 0); // disable on fault
}
void IStatusUpdate_clear(void) { HS_CTRL &= ~(1 << 0); }
void IStatusUpdate_send(void) { /* TODO: implement serial/LIN update */ }
