#include "position_sensor_interface.h"

static int last_position = 0;

// Simulate hardware sensor read
static int hardware_sensor_read(void) {
    // Replace with actual hardware read
    return 50;
}

int position_sensor_read(void) {
    int raw = hardware_sensor_read();
    // Simple filter: clamp to 0-100
    if (raw < 0) raw = 0;
    if (raw > 100) raw = 100;
    last_position = raw;
    return last_position;
}

int position_sensor_last(void) {
    return last_position;
}
