#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "display.h"

// ⚙️ Configuración LCD
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 4

static LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void displayInit() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Sistema OK");
}

void displayClear() {
  lcd.clear();
}

void displayPrintValue(long value) {
  lcd.setCursor(0, 1);
  lcd.print("Valor:       ");
  lcd.setCursor(7, 1);
  lcd.print(value);
}

void displayPrintMessage(const char* line1, const char* line2) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(line1);

  if (line2 != nullptr) {
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}
