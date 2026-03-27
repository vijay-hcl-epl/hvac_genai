#include "flap_controller.h"

int main(void) {
    uint8_t cmd = 50; // Example: mid-position
    FlapController_ReceiveAndValidateCommand(cmd);

    do {
        FlapController_UpdateMotor(cmd);
        FlapController_UpdateStatusIndicator();
    } while (FlapController_ReadCurrentPosition() != cmd);

    FlapController_UpdateStatusIndicator(); // Final update
    return 0;
}
