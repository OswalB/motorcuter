#pragma once
#include <stdint.h>

enum Align {
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

/* Texto crudo */
void lcdFmtText(
  uint8_t col,
  uint8_t row,
  const char* text,
  uint8_t width,
  Align align
);

/* Enteros */
void lcdFmtInt(
  uint8_t col,
  uint8_t row,
  int value,
  uint8_t width,
  Align align
);

/* Booleanos (ON/OFF, CW/CCW, etc.) */
void lcdFmtBool(
  uint8_t col,
  uint8_t row,
  bool value,
  uint8_t width,
  const char* trueTxt,
  const char* falseTxt
);

/* Limpia un área rectangular */
void lcdClearArea(
  uint8_t col,
  uint8_t row,
  uint8_t width
);
