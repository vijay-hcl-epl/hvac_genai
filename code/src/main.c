/**
 @file main.c
 @brief Application integration for HVAC Flap Actuator.
 @responsibility: Initializes, orchestrates, and runs all software units.
 Contains NO local business logic. Control loop only.
*/
#include "hw_abstraction.h"
#include "command_handler.h"
#include "flap_control.h"
#include "position_feedback.h"
#include "indication_manager.h"
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    /* Platform initialization (MCU Nucleo, HAL, clocks, etc.) */
    // HAL_Init();
    // SystemClock_Config();

    /* Hardware layer initialization */
    HW_GPIO_Init();
    HW_UART_Init();
    HW_ADC_Init();
    HW_PWM_Init();

    /* Software Units Init */
    CommandHandler_Init();
    PositionFeedback_Init();
    IndicationManager_Init();
    FlapControl_Init();

    /* State variables for main loop */
    bool sys_power_on = true;
    uint8_t current_position = 0U;
    bool position_valid = false;
    uint8_t target_position = 0U;
    uint8_t uart_byte = 0U;

    IndicationManager_Update(sys_power_on, current_position, false);

    while (1)
    {
        if (HW_UART_Receive(&uart_byte))
        {
            if (CommandHandler_ProcessByte(uart_byte, &target_position))
            {
                /* Valid command accepted, processed above */
            }
        }
        PositionFeedback_Update();
        position_valid = PositionFeedback_IsValid();
        current_position = PositionFeedback_GetCurrentPosition();
        FlapControl_Process(
            CommandHandler_GetTargetPosition(),
            current_position,
            position_valid
        );
        IndicationManager_Update(sys_power_on, current_position, position_valid);
        /* Optionally, add watchdog reset or a short delay for stability. */
    }
}

void SystemClock_Config(void)
{
    /* User must provide board clock init/setup code here */
}
