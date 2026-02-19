#include "uch.h"
#include "appl.h"
#include "fa.h"
#include "mc.h"
#include "si.h"
#include <stdint.h>
#include <stdbool.h>
int main(void) {
    uch_cmd_ctx_t uch_ctx;
    uch_init(&uch_ctx);
    fa_init();
    si_init();
    mc_init();
    appl_init();
    while (1) {
        // Emulated UART/command input
        uint8_t cmd;
        if (uch_get_valid_command(&cmd)) {
            appl_process_command(cmd);
        }
        appl_tick(); // FSM tick
        fa_update();
    }
    return 0;
}
