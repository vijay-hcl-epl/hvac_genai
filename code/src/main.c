#include "command_processor.h"
#include <stdio.h>

int main(void) {
    ApplicationState_t app_state = STATE_IDLE;
    UserCommand_t test_cmd = { .command_id = 1, .data = {0xAA, 0x55}, .data_len = 2 };

    printf("Initial state: %d\n", app_state);
    printf("Processing a test user command...\n");
    ProcessAndExecuteUserCommand(&app_state, &test_cmd);
    printf("Final state: %d\n", app_state);

    return 0;
}
