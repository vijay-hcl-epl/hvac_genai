#include "InitializationStartupUnit.h"
#include "PositionRangeConfigurationUnit.h"
#include "OutputIndicationUnit.h"
#include "FlapPositionControlUnit.h"
#include "FeedbackSensingUnit.h"
#include "InputHandlingUnit.h"

int main(void) {
    // Deterministic initialization
    InitializationStartupUnit_resp_1();
    InitializationStartupUnit_resp_2();
    PositionRangeConfigurationUnit_resp_1();
    PositionRangeConfigurationUnit_resp_2();
    OutputIndicationUnit_resp_1();

    while (1) {
        FeedbackSensingUnit_resp_1();
        FeedbackSensingUnit_resp_2();
        InputHandlingUnit_resp_1();
        InputHandlingUnit_resp_2();
        FlapPositionControlUnit_resp_1();
        FlapPositionControlUnit_resp_2();
        FlapPositionControlUnit_resp_3();
        FlapPositionControlUnit_resp_4();
        // Add fixed order only; deterministic loop
    }
    return 0;
}
