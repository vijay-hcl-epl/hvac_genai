#include "Test_Manager.h"
#include <string.h>

void Test_Manager_Init(TestManager_t *tm) {
    tm->state = TEST_IDLE;
    memset(tm->uart_buffer, 0, sizeof(tm->uart_buffer));
}

void Test_Manager_Exec(TestManager_t *tm, const char *cmd) {
    if(cmd == NULL) return;
    strncpy(tm->uart_buffer, cmd, sizeof(tm->uart_buffer)-1);
    if(strcmp(cmd, "RUN_TEST") == 0) {
        tm->state = TEST_RUNNING;
        // Trigger input handler, LED, and motor test procedures (stub)
        tm->state = TEST_DONE;
    } else {
        // Ignore invalid commands
        tm->state = TEST_IDLE;
    }
}
