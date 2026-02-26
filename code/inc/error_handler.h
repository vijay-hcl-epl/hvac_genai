#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdint.h>
typedef enum { NO_FAULT, HW_FAULT, COMM_FAULT, ADC_FAULT, CONFIG_FAULT } FaultStatus;
void IErrorHandler_notify(uint8_t code, int source_unit);
#endif
