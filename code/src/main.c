#include "system_startup.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "feedback_processor.h"
#include <stdint.h>

int main(void) {
    system_startup_init();
    while (1) {
        // Poll for UART byte (abstracted)
        // Assume UART polling placed here, or driven externally
        flap_control_event();
        feedback_processor_update();
    }
    return 0;
}
