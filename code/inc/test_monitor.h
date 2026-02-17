#ifndef TEST_MONITOR_H
#define TEST_MONITOR_H
#include <stdint.h>

void Test_enable(uint8_t en);
uint8_t Test_query(uint8_t query);
uint8_t Test_status(void);

#endif // TEST_MONITOR_H
