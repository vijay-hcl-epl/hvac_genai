#include "Feedback_Sensor.h"

void Feedback_Sensor_Init(FeedbackSensor_t *fs) {
    fs->state = FS_IDLE;
    for (int i = 0; i < 6; ++i) {
        fs->adc_samples[i] = 0;
        fs->position_map[i] = i; // Fixed mapping
    }
    fs->position = 0;
    fs->is_adc_valid = 1;
}

void Feedback_Sensor_Sample(FeedbackSensor_t *fs, int adc_value) {
    fs->state = FS_SAMPLING;
    int mapped = adc_value / 100; // Dummy logic
    if (mapped >= 0 && mapped < 6) {
        fs->position = mapped;
        fs->is_adc_valid = 1;
    } else {
        fs->is_adc_valid = 0;
    }
    fs->state = FS_UPDATE;
}

void Feedback_Sensor_Update(FeedbackSensor_t *fs) {
    // Placeholder (logic in sample)
    fs->state = FS_IDLE;
}
