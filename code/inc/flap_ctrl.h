#ifndef FLAP_CTRL_H
#define FLAP_CTRL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOVE_IDLE = 0,
    MOVE_CW,
    MOVE_CCW
} move_dir_t;

void FlapCtrl_Init(void);
void FlapCtrl_Step(uint8_t cur_pos, uint8_t target_pos, bool error);
void FlapCtrl_Stop(void);
bool FlapCtrl_IsMoving(void);
move_dir_t FlapCtrl_GetMoveDir(void);

#endif /* FLAP_CTRL_H */
