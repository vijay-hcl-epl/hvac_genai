#include "CommandHandler.h"
#include "FlapControlLogic.h"
#include "ErrorHandler.h"

#define RX_BUF_SIZE 8 // Enough for command + safety margin
static uint8_t rxBuf[RX_BUF_SIZE];
static uint8_t rxIndex = 0;
static bool latestValid = false;
static uint8_t latestPos = 0xFF;

// Allowed positions (0..5)
#define MIN_POS 0
#define MAX_POS 5

void CommandHandler_Init(void) {
    rxIndex = 0;
    latestValid = false;
    latestPos = 0xFF;
}

void CommandHandler_ProcessRx(uint8_t byte) {
    if (byte >= '0' && byte <= '5') {
        uint8_t pos = byte - '0';
        if (pos >= MIN_POS && pos <= MAX_POS) {
            latestValid = true;
            latestPos = pos;
            FlapControlLogic_SetTargetPosition(pos);
        } else {
            ErrorHandler_Report(ERROR_INVALID_COMMAND);
        }
    } else {
        ErrorHandler_Report(ERROR_INVALID_COMMAND);
    }
}

bool CommandHandler_GetLatestCommand(uint8_t *pos) {
    if (latestValid && pos) {
        *pos = latestPos;
        latestValid = false;
        return true;
    }
    return false;
}
