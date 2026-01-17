#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void displayInit();
void displayClear();

// helpers básicos
void displayPrintValue(long value);
void displayPrintMessage(const char* line1, const char* line2 = nullptr);

#endif
