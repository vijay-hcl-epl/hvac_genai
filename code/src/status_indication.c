#include "status_indication.h"
#include <stdbool.h>
static bool led_states[6] = {false};
void status_indication_init(void) {
    for(int i=0;i<6;i++) led_states[i]=false;
    led_states[0]=true; // Power-on LED
}
void status_update_leds(uint8_t position) {
    for(int i=0;i<6;i++) led_states[i]=false;
    if(position<6) led_states[position]=true;
}
