#include "state_machine.h"
#include "command_interface.h"
#include "adc_feedback.h"
#include "motor_control.h"
#include "status_indication.h"
#include "error_handler.h"
#include "config_manager.h"
int main(void) {
    // Startup: init config
    ConfigTable cfg;
    IFlashConfig_get(&cfg);
    while (1) {
        IStateMachine_run();
    }
    return 0;
}
