#include "startup.h"
#include "flap_ctrl.h"
int main(void) {
    Startup_Sequence();
    while (1) {
        Flap_Ctrl_Tick();
        // insert wait/delay
    }
    return 0;
}
