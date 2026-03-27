#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static HardwareAbstractionLayer_t g_HAL_ctx;

void HardwareAbstractionLayer_Init(HardwareAbstractionLayer_t *ctx) {
    ctx->state = HAL_STATE_IDLE;
    ctx->physical_position = 0;
}

void HardwareAbstractionLayer_MoveFlap(uint8_t position) {
    ElectricalInterfaceDriver_SetFlapPosition(position);
    g_HAL_ctx.state = HAL_STATE_MOVING;
}

int HardwareAbstractionLayer_IsMoveComplete(void) {
    // Query underlying feedback
    if(ElectricalInterfaceDriver_FlapAtTarget()) {
        g_HAL_ctx.state = HAL_STATE_IDLE;
        return 1;
    } else {
        return 0;
    }
}
