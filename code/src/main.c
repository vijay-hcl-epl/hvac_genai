#include "Test_Manager.h"
#include "Input_Command_Handler.h"
#include "Status_Indicator.h"
#include "Flap_Position_Controller.h"
#include "System_Startup_Manager.h"
#include "Feedback_Sensor.h"
#include "Calibration_Store.h"

TestManager_t g_test_mgr;
InputCmdHandler_t g_cmd_handler;
StatusIndicator_t g_status_ind;
FlapPositionController_t g_flap_ctrl;
SystemStartupManager_t g_sys_startup;
FeedbackSensor_t g_feedback;
CalibrationStore_t g_calib;

int main(void) {
    // System startup
    System_Startup_Init(&g_sys_startup);
    System_Startup_Sequence(&g_sys_startup);
    // Calibration
    Calibration_Store_Init(&g_calib);
    // Feedback sensor
    Feedback_Sensor_Init(&g_feedback);
    // Status indicator
    Status_Indicator_Init(&g_status_ind);
    // Input handler
    InputCmdHandler_Init(&g_cmd_handler);
    // Flap controller
    Flap_Controller_Init(&g_flap_ctrl);
    // Test manager
    Test_Manager_Init(&g_test_mgr);

    // Main control loop (stub)
    while (1) {
        // Simulate receiving a command (stub)
        // InputCmdHandler_Receive(&g_cmd_handler, "2");
        // InputCmdHandler_Process(&g_cmd_handler);
        // ...
        break; // Single loop for demo
    }
    return 0;
}
