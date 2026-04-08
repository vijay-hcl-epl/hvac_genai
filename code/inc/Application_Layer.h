#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

typedef enum {
    AL_IDLE,
    AL_COMMAND_RECEIVED,
    AL_PROCESSING,
    AL_DONE
} AL_State_t;

typedef enum {
    AL_EVENT_NONE,
    AL_COMMAND_ARRIVAL,
    AL_PROCESSING_COMPLETE
} AL_Event_t;

typedef struct {
    int command_type;
    int target_position;
} AL_UserCommand_t;

void AL_Init(void);
void AL_DispatchCommand(const AL_UserCommand_t* cmd);
void AL_Task(void);

#endif // APPLICATION_LAYER_H
