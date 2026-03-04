#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H

int FlapControl_SetTargetPosition(int pos);
int FlapControl_FeedbackUpdate(int pos, int is_valid);
int FlapControl_Service(void);

#endif // FLAP_CONTROL_H
