#include "led_status_indicator.h"
#include <string.h>

void led_status_indicator_resp_1(led_status_indicator_t *ctx) {
    /* On system state change, update power LED output. */
    ctx->power_led_state = 1u;
}

void led_status_indicator_resp_2(led_status_indicator_t *ctx) {
    /* On flap position update, select only 1 green LED corresponding to mapped position. */
    (void)memset(ctx->green_led_states, 0, sizeof(ctx->green_led_states));
    ctx->green_led_states[0] = 1u; /* default position, actual logic elsewhere */
}

void led_status_indicator_resp_3(led_status_indicator_t *ctx) {
    /* On initialization or change, always keep at most 1 green position LED ON. */
    uint8_t sum = 0u;
    for(uint8_t i=0; i<6; ++i) {
        sum += ctx->green_led_states[i];
    }
    if(sum > 1u) {
        for(uint8_t i=1; i<6; ++i) {
            ctx->green_led_states[i] = 0u;
        }
    }
}
