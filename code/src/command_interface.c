// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf UART/LIN 20.4 Register Description p.369+
#include "command_interface.h"
#include "error_handler.h"
static volatile uint8_t ReceivedCommand = 0;
static volatile DecodingStatus DecStatus = CMD_INVALID;
DecodingStatus ICommandDecoder_getCommand(uint8_t* value) {
    if (DecStatus == CMD_VALID) {
        *value = ReceivedCommand;
        return CMD_VALID;
    }
    return DecStatus;
}
void ICommandDecoder_onRxEvent(uint8_t data_byte) {
    if (data_byte <= 5) {
        ReceivedCommand = data_byte;
        DecStatus = CMD_VALID;
    } else {
        DecStatus = CMD_OUT_OF_RANGE;
        IErrorHandler_notify(1, 0); // code=1: invalid cmd, source=cmd interface
    }
}
