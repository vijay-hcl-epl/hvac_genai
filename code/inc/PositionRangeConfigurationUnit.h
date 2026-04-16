#ifndef POSITIONRANGECONFIGURATIONUNIT_H
#define POSITIONRANGECONFIGURATIONUNIT_H

typedef struct {
    int adc_ranges[6][2]; // [min, max] for 6 positions
} PositionRangeTable;

typedef enum {
    DefineRanges,
    BroadcastConfig
} PositionRangeConfigState;

void PositionRangeConfigurationUnit_resp_1();
void PositionRangeConfigurationUnit_resp_2();

#endif
