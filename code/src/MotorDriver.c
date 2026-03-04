#include "MotorDriver.h"
#include "GPIO.h"
#include "ErrorHandler.h"
static int8_t state = 0; // -1 = reverse, 0 = stopped, 1 = forward
void MotorDriver_Init(void) { state = 0; }
void MotorDriver_SetMove(int8_t direction) {
    if (direction == 1) {
        GPIO_Set(0); // For example: set forward pin
        GPIO_Clear(1);
        state = 1;
    } else if (direction == -1) {
        GPIO_Set(1); // set reverse pin
        GPIO_Clear(0);
        state = -1;
    } else {
        ErrorHandler_Report(21);
    }
}
void MotorDriver_Stop(void) {
    GPIO_Clear(0);
    GPIO_Clear(1);
    state = 0;
}
