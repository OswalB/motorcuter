#include <Arduino.h>
#include <string.h>
#include <display_fmt.h>
#include <display.h>   // aquí sí: 

/* ===== Helpers privados ===== */

static void printAligned(const char* txt, uint8_t width, Align align) {
  char buf[21];  // suficiente para 20x4

  uint8_t len = strlen(txt);
  if (len > width) len = width;

  uint8_t start = 0;
  if (align == ALIGN_CENTER) start = (width - len) / 2;
  else if (align == ALIGN_RIGHT) start = width - len;

  for (uint8_t i = 0; i < width; i++) {
    if (i >= start && i < start + len)
      buf[i] = txt[i - start];
    else
      buf[i] = ' ';
  }
  buf[width] = '\0';

  displayPrint(buf);
}

/* ===== API pública ===== */

void lcdFmtText(uint8_t col, uint8_t row,
                const char* text,
                uint8_t width,
                Align align) {
  displaySetCursor(col, row);
  printAligned(text, width, align);
}

void lcdFmtInt(uint8_t col, uint8_t row,
               int value,
               uint8_t width,
               Align align) {
  char num[12];
  itoa(value, num, 10);

  displaySetCursor(col, row);
  printAligned(num, width, align);
}

void lcdFmtBool(uint8_t col, uint8_t row,
                bool value,
                uint8_t width,
                const char* trueTxt,
                const char* falseTxt) {
  displaySetCursor(col, row);
  printAligned(value ? trueTxt : falseTxt, width, ALIGN_CENTER);
}

void lcdClearArea(uint8_t col, uint8_t row, uint8_t width) {
  displaySetCursor(col, row);
  for (uint8_t i = 0; i < width; i++)
    displayPrintChar(' ');
}
