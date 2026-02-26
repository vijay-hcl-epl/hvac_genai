#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H
typedef enum { STATUS_POSITION, STATUS_FAULT, STATUS_IDLE } StatusType;
void IStatusUpdate_set(StatusType t);
void IStatusUpdate_clear(void);
void IStatusUpdate_send(void);
#endif
