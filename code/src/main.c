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
    return 0;
}
