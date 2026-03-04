#ifndef FEEDBACK_ACQ_PROC_H
#define FEEDBACK_ACQ_PROC_H

#include <stdint.h>

/** Start feedback acquisition (trigger ADC etc.). */
void feedback_acq_start(void);

/** Get the latest measured and mapped position. */
int feedback_acq_get_position(void);

/** Return status of feedback acquisition/validity. */
int feedback_acq_status(void);

#endif // FEEDBACK_ACQ_PROC_H
