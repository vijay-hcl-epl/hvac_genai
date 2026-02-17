#include "user_interface.h"
#include <string.h>
void UI_init(void) { /* [TBD — Init IO/serial if needed] */ }
void UI_status(const char* txbuf) { /* [TBD — Format/send via UART/LIN/LED] */ (void)txbuf; }
uint8_t UI_query(uint8_t cmd) { return 0; /* [TBD — Handle debug query] */ }
