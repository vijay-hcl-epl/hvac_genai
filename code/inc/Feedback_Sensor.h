#ifndef FEEDBACK_SENSOR_H
#define FEEDBACK_SENSOR_H

typedef enum {
    FS_IDLE,
    FS_SAMPLING,
    FS_UPDATE,
    FS_STARTUP
} FeedbackSensorState_t;

typedef struct {
    FeedbackSensorState_t state;
    int adc_samples[6];
    int position_map[6];
    int position;
    int is_adc_valid;
} FeedbackSensor_t;

void Feedback_Sensor_Init(FeedbackSensor_t *fs);
void Feedback_Sensor_Sample(FeedbackSensor_t *fs, int adc_value);
void Feedback_Sensor_Update(FeedbackSensor_t *fs);

#endif // FEEDBACK_SENSOR_H
