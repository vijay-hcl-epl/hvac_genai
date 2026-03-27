#include "Signal_Interface_Manager.h"
#include "Electrical_Interface_Driver.h"

static SignalInterfaceState signal_state = STATE_SIGNAL_IDLE;
static int raw_input_value = 0;
static int norm_command_value = 0;

int SignalInterface_ReadCommand(void) {
    signal_state = STATE_SIGNAL_READ;
    raw_input_value = ElectricalDriver_ReadInput();
    signal_state = STATE_SIGNAL_NORMALIZE;
    // normalize: assume raw input 0-5 maps directly
    norm_command_value = raw_input_value;
    signal_state = STATE_SIGNAL_IDLE;
    return norm_command_value;
}

int SignalInterface_ReadPosition(void) {
    return ElectricalDriver_ReadAdc();
}
