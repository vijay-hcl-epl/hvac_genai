#include "main_control_logic.h"
#include "uart_command_handler.h"
#include "motor_actuator.h"
#include "position_feedback.h"
#include "indicator_control.h"

int main(void) {
  uart_command_handler_init();
  main_control_logic_init();
  motor_actuator_init();
  position_feedback_init();
  indicator_control_init();

  while (1) {
    // Example main loop: poll main control periodically
    main_control_logic_periodic();
    // In real system, would include triggers from UART ISR, timer, etc.
  }
  return 0;
}
