#ifndef FEEDBACK_ACQ_PROC_H
#define FEEDBACK_ACQ_PROC_H
#include <stdint.h>
void feedback_acq_proc_init(void);
void adc_feedback_update(void);
uint8_t get_current_position(void);
#endif // FEEDBACK_ACQ_PROC_H
