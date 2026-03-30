#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include "main.h"
#include "signal_interface_manager.h"

typedef enum {
    APP_IDLE,
    APP_PROCESS_COMMAND,
    APP_FEEDBACK,
    APP_ERROR
} AppState_t;

void APP_ProcessUARTCommand(uint8_t cmd);
void APP_Update(void);

#endif // APPLICATION_LAYER_H
