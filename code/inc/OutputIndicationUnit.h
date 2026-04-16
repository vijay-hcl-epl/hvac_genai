#ifndef OUTPUTINDICATIONUNIT_H
#define OUTPUTINDICATIONUNIT_H

typedef enum {
    PowerOnIndication,
    FlapPositionIndication
} OutputIndicationState;

typedef struct {
    int led_states[7]; // [0]=Power, [1-6]=flap positions
} OutputIndicationLedArray;

void OutputIndicationUnit_resp_1();

#endif
