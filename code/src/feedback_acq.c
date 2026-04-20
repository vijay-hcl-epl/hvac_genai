#include "feedback_acq.h"
#include "config_calib.h"
#include "flap_control.h"
static uint16_t raw_adc_value = 0;
static uint8_t mapped_position = 0;
static bool valid_flag = true;
void update_feedback(void) {
    // TODO: Implement ADC read
    int adc = 0; //mocked
    raw_adc_value = adc;
    //Threshold mapping
    for (int i=0;i<6;i++) {
        if (adc < get_config_param(THRESH_0_ID+i)) {
            mapped_position = i;
            valid_flag = true;
            feedback_update(mapped_position, false);
            return;
        }
    }
    valid_flag = false;
    feedback_update(0, true);
}
uint8_t get_feedback(void) { return mapped_position; }
bool is_feedback_valid(void) { return valid_flag; }
