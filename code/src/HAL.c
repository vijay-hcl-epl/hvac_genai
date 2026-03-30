#include "HAL.h"
#include "ElectricalIfDriver.h"
void HAL_Init(void)
{
    ElectricalIfDriver_Init();
}
uint16_t HAL_GetADC(void)
{
    return ElectricalIfDriver_ReadADC();
}
void HAL_SetGreenLED(uint8_t pos)
{
    ElectricalIfDriver_SetGreenLED(pos);
}
void HAL_StopMotor(void)
{
    ElectricalIfDriver_StopMotor();
}
void HAL_MoveMotor(uint8_t direction)
{
    ElectricalIfDriver_MoveMotor(direction);
}
void HAL_UARTSend(uint8_t data)
{
    ElectricalIfDriver_UARTSend(data);
}
uint8_t HAL_UARTReceive(void)
{
    return ElectricalIfDriver_UARTReceive();
}
