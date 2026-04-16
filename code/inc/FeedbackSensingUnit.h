#ifndef FEEDBACKSENSINGUNIT_H
#define FEEDBACKSENSINGUNIT_H

typedef enum {
    MonitoringADC,
    PositionStatusUpdate
} FeedbackSensingState;

typedef struct {
    int adc_raw_value;
    int position_status;
} FeedbackSensingVars;

void FeedbackSensingUnit_resp_1();
void FeedbackSensingUnit_resp_2();

#endif
