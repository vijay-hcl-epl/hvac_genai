#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

typedef enum {
    TEST_IDLE,
    TEST_RUNNING,
    TEST_DONE
} TestManagerState_t;

typedef struct {
    TestManagerState_t state;
    char uart_buffer[64];
} TestManager_t;

void Test_Manager_Init(TestManager_t *tm);
void Test_Manager_Exec(TestManager_t *tm, const char *cmd);

#endif // TEST_MANAGER_H
