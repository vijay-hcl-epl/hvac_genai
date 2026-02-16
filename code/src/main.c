#include "system_initialization.h"
#include "flap_actuator_controller.h"
#include <stdio.h>
#include <unistd.h> // Only needed for sleep in POSIX sim (mockup)

int main(void) {
    system_init();
    if(!system_is_init_ok()) {
        printf("System initialization failed.\n");
        return -1;
    }
    while(1) {
        flap_actuator_controller_task();
        // platform-specific implement delay - stub
        #ifdef __unix__
        usleep(10000);
        #endif
    }
    return 0;
}
