#include "init_startup.h"
#include "flap_ctrl.h"

int main(void) {
    if (init_start() != 0) {
        // [TBD — Not found: Error flashing, halt]
        return 1;
    }
    while (1) {
        position_controller_execute();
        // [TODO: Insert sleep, watchdog, or event wait for efficiency; not specified]
    }
    return 0;
}
