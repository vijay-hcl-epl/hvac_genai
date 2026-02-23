#ifndef ERROR_SAFE_H
#define ERROR_SAFE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ERR_NONE = 0,
    ERR_INVALID_CMD,
    ERR_ADC_RANGE,
    ERR_HW_FAULT
} error_id_t;

void ErrorSafe_Init(void);
void ErrorSafe_SetError(error_id_t err_id);
void ErrorSafe_ClearError(void);
bool ErrorSafe_IsErrorActive(void);
error_id_t ErrorSafe_GetError(void);

#endif /* ERROR_SAFE_H */
