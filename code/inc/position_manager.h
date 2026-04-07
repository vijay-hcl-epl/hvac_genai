#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H
#include <stdint.h>
typedef enum { POSMGR_ACCEPTED, POSMGR_BUSY } PosMgrStatus_t;
PosMgrStatus_t PositionManager_command(uint8_t pos);
uint8_t get_CurrentPosition(void);
void position_manager_init(void);
#endif // POSITION_MANAGER_H
