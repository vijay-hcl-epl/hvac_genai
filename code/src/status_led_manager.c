#include "status_led_manager.h"
#include <stdint.h>
#include <stdbool.h>

#define LED_POWER_PIN    (4U)
#define LED_ERROR_PIN    (5U)
#define LED_FLAP0_PIN    (6U)
#define LED_FLAP1_PIN    (7U)
#define LED_FLAP2_PIN    (8U)
#define LED_FLAP3_PIN    (9U)

// Dummy GPIO abstraction for platform independence
static void gpio_write(uint8_t pin, bool value) {
    (void)pin; (void)value;
}

void status_led_manager_init(void) {
    gpio_write(LED_POWER_PIN, false);
    gpio_write(LED_ERROR_PIN, false);
    gpio_write(LED_FLAP0_PIN, false);
    gpio_write(LED_FLAP1_PIN, false);
    gpio_write(LED_FLAP2_PIN, false);
    gpio_write(LED_FLAP3_PIN, false);
}

void set_led_status(Led_t led, bool on) {
    uint8_t pin = 0;
    switch(led) {
        case LED_POWER: pin = LED_POWER_PIN; break;
        case LED_ERROR: pin = LED_ERROR_PIN; break;
        case LED_FLAP_POS_0: pin = LED_FLAP0_PIN; break;
        case LED_FLAP_POS_1: pin = LED_FLAP1_PIN; break;
        case LED_FLAP_POS_2: pin = LED_FLAP2_PIN; break;
        case LED_FLAP_POS_3: pin = LED_FLAP3_PIN; break;
        default: return;
    }
    gpio_write(pin, on);
}
