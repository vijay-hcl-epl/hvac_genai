#include "Application_Layer.h"
#include <stdio.h>

int main(void) {
    ApplicationLayer_Init();

    // Example command loop
    for (int i = 0; i < 3; ++i) {
        ApplicationLayer_ReceiveCommand(i + 1);
        while (ApplicationLayer_GetState() != APP_STATE_IDLE && ApplicationLayer_GetState() != APP_STATE_ERROR) {
            ApplicationLayer_Process();
        }
        printf("Cycle %d complete. Final state: %d\n", i + 1, ApplicationLayer_GetState());
    }
    return 0;
}
