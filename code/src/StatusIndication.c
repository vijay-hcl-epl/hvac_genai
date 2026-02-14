#include "StatusIndication.h"
#include "hw_abstraction.h"
#define NUM_LEDS 6
void StatusIndication_Init(void) {
    hw_init_leds();
}
void StatusIndication_SetLed(uint8_t pos) {
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        hw_set_led(i, i == pos);
    }
}
void StatusIndication_PowerLed(bool on) {
    hw_set_power_led(on);
}
