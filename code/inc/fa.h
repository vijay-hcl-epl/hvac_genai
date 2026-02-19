#ifndef FA_H_
#define FA_H_
#include <stdint.h>
#include <stdbool.h>
#define FLAP_POS_MIN 0
#define FLAP_POS_MAX 5
// Out-of-range API
bool fa_is_oor(void);
uint8_t fa_get_pos(void);
void fa_update(void);
void fa_init(void);
#endif
