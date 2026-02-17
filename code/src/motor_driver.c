#include "motor_driver.h"
// [TBD — Not in source]: Register macros, BDRV, GPT1
static MotorConfig g_motor_cfg;
void Motor_init(const MotorConfig* config) { g_motor_cfg = *config; /* [TBD — HW init] */ }
uint8_t Motor_run(MotorDirection dir, uint16_t speed) { return 0; /* [TBD — HW run] */ }
void Motor_stop(void) { /* [TBD — HW stop] */ }
uint8_t Motor_status(void) { return 0; /* [TBD — HW stat] */ }
