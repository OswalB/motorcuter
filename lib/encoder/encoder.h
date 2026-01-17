#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

void encoderInit();
void encoderUpdate();
long encoderGetValue();

bool encoderButtonPressed();
#endif
