#include "uart_command_handler.h"
#include "position_feedback.h"

int main(void) {
    // Initialization
    // Main loop stub
    while (1) {
        position_feedback_notify();
    }
    return 0;
}
