#ifndef SYSTEM_INITIALIZATION_AND_SAFETY_UNIT_H
#define SYSTEM_INITIALIZATION_AND_SAFETY_UNIT_H
// Structs from Internal Data Design
typedef struct {
    int init_state;
    int led_status;
    int motor_startup_state;
} SystemInitInternalData;

// Enums from State Machine
typedef enum {
    STATE_SYSTEM_INIT,
    STATE_MONITOR_ADC
} SystemInitState;

// Function declarations
void System_Initialization_and_Safety_Unit_resp_0(void);
void System_Initialization_and_Safety_Unit_resp_1(void);

#endif /* SYSTEM_INITIALIZATION_AND_SAFETY_UNIT_H */
