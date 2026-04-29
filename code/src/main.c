#include "input_handler.h"
#include "position_acquisition.h"
#include "control_command.h"
#include "status_indication.h"

int main(void)
{
    // Initialization
    UpdatePosition();
    valid_command_flag = 0;
    error_state_flag = 0;
    SetLEDs(0);

    while (1)
    {
        int desired_position = 0;
        if (GetUserCommand(&desired_position) == USER_CMD_POSITION)
        {
            SetFlapPosition(desired_position);
        }
        UpdatePosition();
        ControlCommandMain();
        UpdateStatusIndicator();
        // TODO: Insert delay or RTOS tick here
    }
    return 0;
}
