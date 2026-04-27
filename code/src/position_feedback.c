#include "position_feedback.h"
#include "main_control_logic.h"

// ADC range map (dummy values)
typedef struct { int min; int max; } adc_map_t;
static const adc_map_t adc_map[LOGICAL_POSITIONS] = {
  {0, 204}, {205, 409}, {410, 614}, {615, 819}, {820, 1023}
};

void position_feedback_init(void) {}
static int sample_adc(void) {
  // HW: Read ADC and return value
  return 0; // stub
}

void position_feedback_poll(void) {
  int adc_val = sample_adc();
  bool in_range = false;
  uint8_t logical = 0xFF;
  for (int i = 0; i < LOGICAL_POSITIONS; ++i) {
    if (adc_val >= adc_map[i].min && adc_val <= adc_map[i].max) {
      logical = i;
      in_range = true;
      break;
    }
  }
  main_control_logic_on_position_feedback(logical, adc_val, in_range);
}
