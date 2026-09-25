/**
 * @file main.c
 * @brief Application entry point – init + main task dispatcher (super-loop).
 *
 * Traces: SWE-REQ-020, SWE-REQ-021, SWE-REQ-022, SWE-REQ-033, SWE-REQ-034
 * Platform: STM32F407G-DISC1 / STM32 HAL / Bare-metal
 *
 * Execution model: bare-metal super-loop; no RTOS [SWE-REQ-026].
 */

#include "stm32f4xx_hal.h"
#include "system_init.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "flap_control_logic.h"
#include "led_status_handler.h"
#include "motor_driver.h"

/**
 * @brief Main application entry point.
 * @return Does not return (infinite loop).
 */
int main(void)
{
    /* ---- STEP 1: Full system initialisation [SWE-REQ-020] ---- */
    system_init();

    /* ---- STEP 2: Read initial feedback and update LEDs [SWE-REQ-021] ---- */
    feedback_processor_update();
    {
        uint8_t init_pos = 0U;
        if (feedback_processor_get_position(&init_pos) != 0U)
        {
            led_status_set_position(init_pos);
        }
    }

    /* ---- STEP 3: Main task dispatcher (super-loop) ---- */
    while (1)
    {
        /* 3a. Poll UART for new commands [SWE-REQ-022] */
        command_parser_update();

        /* 3b. Acquire and validate feedback [SWE-REQ-010] */
        feedback_processor_update();

        /* 3c. Run flap control state machine [SWE-REQ-023, SWE-REQ-033] */
        flap_control_update();
    }

    /* Should never reach here */
    return 0;
}
