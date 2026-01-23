#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <menu.h>

void displayInit();
void displaySetCursor(uint8_t col, uint8_t row);
void displayPrint(const char* txt);
void displayPrintChar(char c);

void displayRenderMenu();
void displayRenderStatus();
void displayClear();

#endif

