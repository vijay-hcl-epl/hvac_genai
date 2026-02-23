#include "status_indication.h"
#include "hw_abstraction.h"

void status_indication_init(void)
{
    // All LEDs off at startup
    for(int i=0; i<=5; ++i) hw_gpio_set(POS_LED_PIN_0 + i, 0);
    hw_gpio_set(POWER_LED_PIN, 0);
}

void status_indication_update_leds(bool power_on, uint8_t pos_idx)
{
    hw_gpio_set(POWER_LED_PIN, power_on ? 1 : 0);
    for(int i=0; i<=5; ++i)
    {
        hw_gpio_set(POS_LED_PIN_0 + i, (i == pos_idx) ? 1 : 0);
    }
}
