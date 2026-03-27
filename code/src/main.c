#include "Application_Layer.h"
#include <stdio.h>

int main(void) {
    ApplicationContext_t app_ctx;
    ApplicationLayer_Init(&app_ctx);

    UserCommand_t user_cmd = { .command_id = 1, .param = 50 };
    ApplicationLayer_ProcessCommand(&app_ctx, &user_cmd);

    printf("State: %d\n", ApplicationLayer_GetState(&app_ctx));
    printf("Output Triggered: %u\n", ApplicationLayer_GetOutputStatus(&app_ctx));

    return 0;
}
