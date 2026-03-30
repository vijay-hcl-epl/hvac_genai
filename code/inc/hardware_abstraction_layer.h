#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include "main.h"

// API parameter wrappers and peripheral access

typedef struct {
    ADC_HandleTypeDef* hadc;
    UART_HandleTypeDef* huart;
    TIM_HandleTypeDef* htim_pwm;
    GPIO_TypeDef* gpio_port_motor;
    uint16_t gpio_pin_motor_dir1;
    uint16_t gpio_pin_motor_dir2;
    GPIO_TypeDef* gpio_port_led;
    uint16_t gpio_pins_led[6];
} HAL_PeripheralConfig;

// Hardware Access Functions
void HAL_InitPeripherals(const HAL_PeripheralConfig* config);
int HAL_SetMotorPosition(int position);
int HAL_ReadFlapPosition(void);
void HAL_SetLED(uint8_t led_idx, uint8_t state);
void HAL_AllLEDOff(void);

#endif // HARDWARE_ABSTRACTION_LAYER_H
