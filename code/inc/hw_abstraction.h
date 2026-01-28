/**
 @file hw_abstraction.h
 @brief Hardware Abstraction Layer for STM32F407G-DISC1
UART, ADC, GPIO(LED), and PWM/Motor driver interfaces.
 @responsibility Provides platform abstraction for all hardware IOs as per SWE-REQ-018..022; Forwards STM32 HAL calls; Not for application logic.
*/
#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H
#include <stdint.h>
#include <stdbool.h>

/* Motor direction enum */
typedef enum { MOTOR_DIR_CW = 0, MOTOR_DIR_CCW } MotorDirection_t;

/* UART */
void HW_UART_Init(void); /* SWE-REQ-018 */
bool HW_UART_Receive(uint8_t *rxByte); /* SWE-REQ-018 */
void HW_UART_IRQHandler(void); /* IRQ handler stub */

/* ADC */
void HW_ADC_Init(void); /* SWE-REQ-019 */
uint16_t HW_ADC_Read(void); /* SWE-REQ-019 */

/* GPIO (LED) */
void HW_GPIO_Init(void); /* SWE-REQ-022 */
void HW_LED_Set(uint8_t led_index, bool state); /* SWE-REQ-022 */

/* PWM/Motor */
void HW_PWM_Init(void); /* SWE-REQ-021 */
void HW_Motor_SetDirection(MotorDirection_t direction); /* SWE-REQ-020 */
void HW_Motor_Enable(bool enable); /* SWE-REQ-021 */

#endif /* HW_ABSTRACTION_H */
