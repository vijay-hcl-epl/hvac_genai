#include "main_coordinator.h"
#include "uart_cmd_handler.h"
#include "motor_control.h"
#include "feedback_processor.h"
#include "led_control.h"

int main(void)
{
    coordinator_init();
    while (1)
    {
        coordinator_main_loop();
    }
    /* MISRA: Rule 14.10 – All code paths should return a value in non-void functions */
    return 0;
}
