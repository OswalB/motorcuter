/*
 * Uso:
 *   lcdFmtInt(col, row, value, width, align, fmt);
 */

#include <Arduino.h>
#include <string.h>
#include <display_fmt.h>
#include <display.h> 


/* =========================================================
 * Tipos internos
 * ========================================================= */

typedef const char* (*FmtFn)(
  int value,
  char* buffer,
  size_t bufSize
);

/* =========================================================
 * Forward declarations ()
 * ========================================================= */
static const char* fmtWithUnit(FmtFn baseFmt, int value, UnitType unit, char* buffer, size_t bufSize);

static const char* fmtRaw(int value, char* buffer, size_t bufSize);
static const char* fmtMode(int value, char* buffer, size_t bufSize);
static const char* fmtBool(int value, char* buffer, size_t bufSize);
static const char* fmtDec1(int value, char* buffer, size_t bufSize);
static const char* fmtDec2(int value, char* buffer, size_t bufSize);
static const char* fmtDec1Sec(int value, char* buffer, size_t bufSize);
static const char* fmtDec1Ms(int value, char* buffer, size_t bufSize);
static const char* fmtRpm(int value, char* buffer, size_t bufSize);

/* =========================================================
 * Tablas de equivalencia
 * ========================================================= */

 static const char* MODE_STR[] = {
  "STOP",
  "CONT",
  "TIMED",
  "EVENT"
};

/* Dispatcher principal */
static const FmtFn FORMATTERS[] = {
  fmtRaw,     // FMT_RAW
  fmtMode,    // FMT_MODE
  fmtBool,    // FMT_BOOL
  fmtDec1,    // FMT_DEC_1
  fmtDec2,    // FMT_DEC_2
  fmtDec1Sec, // FMT_DEC1_S
  fmtDec1Ms,  // FMT_DEC1_MS
  fmtRpm      // FMT_RPM
};

/* =========================================================
 * Helpers privados
 * ========================================================= */

static void formatScaledDecimal(int value,
                                uint8_t decimals,
                                char* out,
                                size_t outSize) {
  int scale = 1;
  for (uint8_t i = 0; i < decimals; i++) scale *= 10;

  int ip = value / scale;
  int fp = abs(value % scale);

  // Parte entera
  itoa(ip, out, 10);

  size_t len = strlen(out);
  if (len + 1 >= outSize) return;

  out[len++] = '.';

  // Parte fraccional con padding manual
  for (int i = decimals - 1; i >= 0; i--) {
    int d = (fp / (int)pow(10, i)) % 10;
    if (len < outSize - 1) {
      out[len++] = '0' + d;
    }
  }

  out[len] = '\0';
  
  //snprintf(out, outSize, "%d.%0*d", ip, decimals, fp);
}

static void printAligned(const char *txt, uint8_t width, Align align)
{
  char buf[21]; // suficiente para 20x4

  uint8_t len = strlen(txt);
  if (len > width)
    len = width;

  uint8_t start = 0;
  if (align == ALIGN_CENTER)
    start = (width - len) / 2;
  else if (align == ALIGN_RIGHT)
    start = width - len;

  for (uint8_t i = 0; i < width; i++)
  {
    if (i >= start && i < start + len)
      buf[i] = txt[i - start];
    else
      buf[i] = ' ';
  }
  buf[width] = '\0';

  displayPrint(buf);
}

/* =========================================================
 * Implementación de formatters
 * ========================================================= */


static const char* fmtRaw(int value, char* buffer, size_t bufSize) {
  itoa(value, buffer, 10);
  return buffer;
}

static const char* fmtMode(int value, char*, size_t) {
  if (value < 0 || value >= 4) return "UNKN";
  return MODE_STR[value];
}

static const char* fmtBool(int value, char*, size_t) {
  return value ? "ON" : "OFF";
}

static const char* fmtDec1(int value, char* buffer, size_t bufSize) {
  formatScaledDecimal(value, 1, buffer, bufSize);
  return buffer;
}

static const char* fmtDec2(int value, char* buffer, size_t bufSize) {
  formatScaledDecimal(value, 2, buffer, bufSize);
  return buffer;
}

static const char* fmtDec1Sec(int value, char* buffer, size_t bufSize) {
  return fmtWithUnit(fmtDec1, value, UNIT_S, buffer, bufSize);
}

static const char* fmtDec1Ms(int value, char* buffer, size_t bufSize) {
  return fmtWithUnit(fmtDec1, value, UNIT_MS, buffer, bufSize);
}

static const char* fmtRpm(int value, char* buffer, size_t bufSize) {
  return fmtWithUnit(fmtRaw, value, UNIT_RPM, buffer, bufSize);
}



/* ---- formatter con unidad ---- */



static const char* UNIT_STR[] = {
  "",
  "RPM",
  "ms",
  "s"
};

static const char* fmtWithUnit(FmtFn baseFmt,
                               int value,
                               UnitType unit,
                               char* buffer,
                               size_t bufSize) {
  char tmp[16];
  baseFmt(value, tmp, sizeof(tmp));

  snprintf(buffer, bufSize, "%s %s",
           tmp,
           UNIT_STR[unit]);

  return buffer;
}

/*static const char* fmtDec1Sec(int value, char* buffer, size_t bufSize) {
  return fmtWithUnit(fmtDec1, value, UNIT_S, buffer, bufSize);
}*/


/* =========================================================
 * API pública
 * ========================================================= */

void lcdFmtText(uint8_t col, uint8_t row,
                const char *text,
                uint8_t width,
                Align align)
{
  displaySetCursor(col, row);
  printAligned(text, width, align);
}

void lcdFmtInt(uint8_t col, uint8_t row,
               int value,
               uint8_t width,
               Align align,
               FmtType fmt)
{
  //char num[12];
  //itoa(value, num, 10);

  displaySetCursor(col, row);
  char tmp[16];
  const char* txt = nullptr;

  if (fmt < (sizeof(FORMATTERS) / sizeof(FORMATTERS[0]))) {
    txt = FORMATTERS[fmt](value, tmp, sizeof(tmp));
  }

  if (!txt) {
    itoa(value, tmp, 10);
    txt = tmp;
  }

  //printAligned(num, width, align);

  printAligned(txt, width, align);
}

void lcdFmtBool(uint8_t col, uint8_t row,
                bool value,
                uint8_t width,
                const char *trueTxt,
                const char *falseTxt)
{
  displaySetCursor(col, row);
  printAligned(value ? trueTxt : falseTxt, width, ALIGN_CENTER);
}

void lcdClearArea(uint8_t col, uint8_t row, uint8_t width)
{
  displaySetCursor(col, row);
  for (uint8_t i = 0; i < width; i++)
    displayPrintChar(' ');
}
