#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdbool.h>

// Allowed range for flap position
#define FLAP_POSITION_MIN 0
#define FLAP_POSITION_MAX 100

// User Command API
bool input_handler_validate(int input_value);
int input_handler_get_last_valid(void);

#endif // INPUT_HANDLER_H
