#include "uart_handler.h"
#include "main_control.h"
#include "motor_actuator.h"
#include "position_feedback.h"
#include "indicator_control.h"

int main(void) {
    uart_init();
    main_control_init();
    motor_init();
    position_feedback_init();
    indicator_init();

    while (1) {
        // Main loop stub
    }
    return 0;
}
