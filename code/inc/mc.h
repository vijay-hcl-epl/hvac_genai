#ifndef MC_H_
#define MC_H_
#include <stdint.h>
typedef enum { MC_OFF, MC_FWD, MC_REV } mc_state_t;
void mc_init(void);
void mc_move(int dir); // 1=fwd, -1=rev
void mc_stop(void);
mc_state_t mc_get_state(void);
#endif
