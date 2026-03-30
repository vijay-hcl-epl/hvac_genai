#include "ElectricalIfDriver.h"
// Stub implementations for hardware IO
void ElectricalIfDriver_Init(void) {}
uint16_t ElectricalIfDriver_ReadADC(void) { return 0U; }
void ElectricalIfDriver_SetGreenLED(uint8_t pos) { (void)pos; }
void ElectricalIfDriver_StopMotor(void) {}
void ElectricalIfDriver_MoveMotor(uint8_t direction) { (void)direction; }
void ElectricalIfDriver_UARTSend(uint8_t data) { (void)data; }
uint8_t ElectricalIfDriver_UARTReceive(void) { return 0U; }
