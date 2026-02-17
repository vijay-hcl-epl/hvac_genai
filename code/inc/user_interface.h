#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <stdint.h>

void UI_init(void);
void UI_status(const char* txbuf);
uint8_t UI_query(uint8_t cmd);

#endif // USER_INTERFACE_H
