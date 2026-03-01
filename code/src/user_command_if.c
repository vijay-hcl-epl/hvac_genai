// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf §19 (UART/LIN), infineon-tle9851qxw-datasheet-en.pdf §18, Table 341
#include "user_command_if.h"
#include "flap_ctrl_logic.h"
#include "error_handler.h"
#define UART_RX_BUF_SZ 8
static uint8_t rx_buf[UART_RX_BUF_SZ];
static uint8_t rx_state = 0;
static uint8_t last_cmd = 0;

void UserCommandIF_Init(void) {
    // Set UART to 8N1 mode, enable RX; configure BRG for baud
    // Ref: SCON.SM0=0, SM1=1; SCON.REN=1; Set BRG registers
}

void Cmd_Received(uint8_t position) {
    if (position <= 5) FlapCtrl_MoveTo(position);
    else Cmd_Error(1);
}
void Cmd_Error(uint8_t reason) {
    // Send NACK or error code over UART
    // Set up error response (via SBUF, wait for TI flag)
    ErrorHandler_FlagError(reason);
}
// [Reception interrupt handler is MCU/OS-dependent and omitted]
