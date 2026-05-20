#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

void position_feedback_init(void);
int position_feedback_read(void);
int position_feedback_map_adc(int adc_value);

#endif
