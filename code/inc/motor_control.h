// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf Capture/Compare Unit 6 (CCU6), 18.10 Register Description, p.790+
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
typedef enum { MCW_STOPPED, MCW_RUNNING, MCW_BRAKE } MotorStatus;
void IMotorControl_start(uint8_t direction, uint16_t pwm);
void IMotorControl_stop(void);
#endif
