#ifndef LED_STATUS_AND_FEEDBACK_UNIT_H
#define LED_STATUS_AND_FEEDBACK_UNIT_H
// Structs from Internal Data Design
typedef struct {
    int power_led;
    int position_leds[10];
} LEDStatusInternalData;

// Enums from State Machine
typedef enum {
    STATE_POWER_LED_ON,
    STATE_SET_GREEN_LED_STATUS
} LEDStatusState;

// Function declarations
void LED_Status_and_Feedback_Unit_resp_0(void);
void LED_Status_and_Feedback_Unit_resp_1(void);

#endif /* LED_STATUS_AND_FEEDBACK_UNIT_H */
