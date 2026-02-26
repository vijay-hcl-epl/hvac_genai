#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
typedef struct {
    uint16_t adc_thresholds[6];
    uint16_t pwm_freq;
    uint8_t  output_map;
    uint8_t  protocol;
} ConfigTable;
int IFlashConfig_get(ConfigTable* ctable);
#endif
