#ifndef LOGICAL_MAPPER_H
#define LOGICAL_MAPPER_H

#include <stdint.h>

#define SYMBOLIC_INVALID -1

typedef enum {
    FLAP_POS_0 = 0,
    FLAP_POS_1,
    FLAP_POS_2,
    FLAP_POS_3,
    FLAP_POS_COUNT
} FlapPosition_t;

int map_to_symbolic(uint16_t raw_val);
const FlapPosition_t* get_supported_positions(void);
int map_error_status(void);

#endif // LOGICAL_MAPPER_H
