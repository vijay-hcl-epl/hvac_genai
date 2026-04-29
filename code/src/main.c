#include "init_coordinator.h"
int main(void) {
    system_init();
    while (1) {
        main_loop();
    }
    return 0;
}
