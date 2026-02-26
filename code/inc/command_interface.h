// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf Ports, 23.4 Register Definition, p.441+
#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H
#include <stdint.h>
typedef enum { CMD_VALID, CMD_INVALID, CMD_OUT_OF_RANGE } DecodingStatus;
DecodingStatus ICommandDecoder_getCommand(uint8_t* value);
void ICommandDecoder_onRxEvent(uint8_t data_byte);
#endif
