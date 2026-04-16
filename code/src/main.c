#include "feedback_sensing_unit.h"
#include "user_input_handling_unit.h"
#include "control_logic_unit.h"
#include "output_indication_unit.h"

int main(void) {
    // Initialize module state variables
    FeedbackSensingUnitData feedback_sensing_unit_data = {0};
    UserInputHandlingUnitData user_input_handling_unit_data = {0};
    ControlLogicUnitData control_logic_unit_data = {0};
    OutputIndicationUnitData output_indication_unit_data = {0};

    while (1) {
        feedback_sensing_unit_resp_0(&feedback_sensing_unit_data);
        user_input_handling_unit_resp_0(&user_input_handling_unit_data);
        user_input_handling_unit_resp_1(&user_input_handling_unit_data);
        control_logic_unit_resp_0(&control_logic_unit_data);
        control_logic_unit_resp_1(&control_logic_unit_data);
        control_logic_unit_resp_2(&control_logic_unit_data);
        output_indication_unit_resp_0(&output_indication_unit_data);
        output_indication_unit_resp_1(&output_indication_unit_data);
    }
    return 0; // never reached
}
