#include "position_sensor_mapper.h"

void position_sensor_mapper_resp_1(position_sensor_mapper_t *ctx) {
    /* Periodically sample potentiometer with ADC. */
    ctx->pot_adc_buffer = 0u; /* stubbed ADC read */
}

void position_sensor_mapper_resp_2(position_sensor_mapper_t *ctx) {
    /* Map raw ADC value to nearest logical position using lookup/comparison against thresholds. */
    for(uint8_t i=0; i<5; ++i) {
        if(ctx->pot_adc_buffer < ctx->pos_thresholds[i]) {
            ctx->logical_position = i;
            return;
        }
    }
    ctx->logical_position = 5u;
}

void position_sensor_mapper_resp_3(position_sensor_mapper_t *ctx) {
    /* Bound check mapped position; set error if outside limits. */
    if(ctx->logical_position > 5u) {
        ctx->logical_position = 0u; /* default to 0 if out of range */
    }
}

void position_sensor_mapper_resp_4(position_sensor_mapper_t *ctx) {
    /* Provide current logical position as output. (Nothing to do in stub)*/
}
