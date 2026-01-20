#ifndef ENCODER_H
#define ENCODER_H

#include "menu_events.h"

void encoderInit();
void encoderUpdate();
long encoderGetValue();

MenuEvent encoderGetEvent();
bool encoderButtonPressed();
#endif
