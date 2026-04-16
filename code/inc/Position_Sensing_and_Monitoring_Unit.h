#ifndef POSITION_SENSING_AND_MONITORING_UNIT_H
#define POSITION_SENSING_AND_MONITORING_UNIT_H
// Structs from Internal Data Design
typedef struct {
    int adc_result;
    int filtered_position;
} PositionSensingInternalData;

// Enums from State Machine
typedef enum {
    STATE_ACQUIRE_ADC_DATA
} PositionSensingState;

// Function declarations
void Position_Sensing_and_Monitoring_Unit_resp_0(void);

#endif /* POSITION_SENSING_AND_MONITORING_UNIT_H */
