#include "hardware_abstraction.h"
#include "input_handler.h"
#include "flap_control_logic.h"

int main(void) {
    hardware_abstraction_init();
    input_handler_init();
    flap_control_logic_init();
    for (;;) {
        flap_control_logic_task();
        // Simulate UART or test input event externally
    }
    return 0;
}
