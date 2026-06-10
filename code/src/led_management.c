#include "led_management.h"
#include "hardware_abstraction.h"

void Set_Status_LED(bool on) {
    GPIO_Write(2, on); // status LED assumed at pin 2
}

void Set_Position_LED(uint8_t pos) {
    // Six position LEDs at pins 10–15
    for (uint8_t i = 0; i < 6; i++)
        GPIO_Write(10 + i, (i == pos));
}
