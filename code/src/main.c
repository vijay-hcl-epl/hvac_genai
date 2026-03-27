#include "Application_Layer.h"
#include <stdio.h>

int main()
{
    ApplicationStatus_t app_status;
    UserCommand_t user_cmd;

    // Example command
    user_cmd.command_id = 1;
    user_cmd.command_param = 42;

    ApplicationLayer_Init(&app_status);

    // Main integration loop (example, single run for demonstration)
    ApplicationLayer_Process(&app_status, &user_cmd);
    ApplicationLayer_Process(&app_status, 0); // Moves to VALIDATING
    ApplicationLayer_Process(&app_status, 0); // Moves to EXECUTING
    ApplicationLayer_Process(&app_status, 0); // Moves to OUTPUT_TRIGGERED
    ApplicationLayer_Process(&app_status, 0); // Moves back to IDLE

    printf("Final State: %d\n", ApplicationLayer_GetState(&app_status));
    return 0;
}
