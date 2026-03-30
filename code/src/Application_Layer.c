#include "Application_Layer.h"

void ApplicationLayer_Init(CommandQueue_t* q) {
    q->head = 0;
    q->tail = 0;
    q->status = 0;
}

void ApplicationLayer_Process(CommandQueue_t* q) {
    static AppState_t state = APP_STATE_IDLE;
    switch(state) {
        case APP_STATE_IDLE:
            // Check for commands
            if(q->head != q->tail) {
                state = APP_STATE_EXECUTE;
            }
            break;
        case APP_STATE_EXECUTE:
            // Consume a command (simulate execution)
            q->status = q->queue[q->tail];
            q->tail = (q->tail + 1) % CMD_QUEUE_SIZE;
            state = APP_STATE_MONITOR;
            break;
        case APP_STATE_MONITOR:
            // Monitor status
            // In real code, would update status, check subsystem
            state = APP_STATE_IDLE;
            break;
    }
}
