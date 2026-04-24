#include "command_interface.h"
#include "position_control.h"
#include <stdlib.h>
#include <string.h>

#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5

static int ci_last_cmd = -1;

void CI_Init(void) {
    ci_last_cmd = -1;
}

// Parse UART RX buffer for a single numeric command.
void CI_ProcessUartInput(const char *rx_buf, uint8_t len) {
    if(len==0 || !rx_buf) return;
    // Accepts 1 or 2 char (position 0-5)
    char tmp[4] = {0};
    if (len >= (sizeof(tmp))) return;
    strncpy(tmp, rx_buf, len);
    char *endptr;
    long val = strtol(tmp, &endptr, 10);
    if (endptr == tmp || *endptr != '\0') return; // not a pure number
    if (val < FLAP_POS_MIN || val > FLAP_POS_MAX) return;
    ci_last_cmd = (int)val;
    PC_NewCommand(ci_last_cmd); // Pass to position control
}
