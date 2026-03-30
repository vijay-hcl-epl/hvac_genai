#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"

void ApplicationLayer_Init(ApplicationLayer_Data_t *data) {
    data->cmd = 0;
    data->cmd_ready = false;
}

void ApplicationLayer_Process(ApplicationLayer_Data_t *data) {
    if (data->cmd_ready) {
        // Decode and validate command
        if (SignalInterfaceManager_ValidateCommand(data->cmd)) {
            // Relay command to hardware layer
            SignalInterfaceManager_RelayCommand(data->cmd);
        }
        // Clear buffer
        data->cmd_ready = false;
    }
}
