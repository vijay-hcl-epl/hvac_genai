#include "position_feedback.h"
#include "main_control_logic.h"

int position_feedback_read(void) {
    // Stub: read ADC and map to logical position
    return 0;
}

void position_feedback_notify(void) {
    int pos = position_feedback_read();
    main_control_update_feedback(pos);
}
