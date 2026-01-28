#pragma once
#include <stdint.h>

enum Align {
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

enum UnitType {
  UNIT_NONE,
  UNIT_RPM,
  UNIT_MS,
  UNIT_S
};

typedef enum {
  FMT_RAW = 0,   // imprime el entero tal cual
  FMT_MODE,      // enum MotorMode -> texto
  FMT_BOOL,
  FMT_DEC_1,
  FMT_DEC_2,
  FMT_DEC1_S,
  FMT_DEC1_MS,
  FMT_RPM,
  FMT_COUNT      // SIEMPRE el último
  
} FmtType;

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
  Align align,
  FmtType fmt
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
