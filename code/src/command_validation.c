#include "command_validation.h"

// Example: valid commands are 0x00 to 0x05 (do not invent extra logic)
bool validate_command(uint8_t command) {
    if (command <= 0x05) {
        return true;
    }
    return false;
}
