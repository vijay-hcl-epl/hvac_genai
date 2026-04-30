#include "led_indication_driver.h"

static LedStatus_t g_led_status = LED_STATUS_OFF;

void set_led_state(LedStatus_t status) {
    // Determine LED pattern based on status. Underlying hardware setting is delegated.
    g_led_status = status;
    // TODO: Hardware update via provided interface
}

LedStatus_t get_led_state(void) {
    return g_led_status;
}

void led_error_status(void) {
    set_led_state(LED_STATUS_ERROR);
}
