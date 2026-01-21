#include <LiquidCrystal_I2C.h>
#include "display.h"
#include "menu.h"

#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

static LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
static uint8_t firstVisible = 0;
static void displayPrintValue(const MenuItem& item);

void displayInit() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void displayRenderMenu() {
  const MenuContext& m = menuGetContext();

  if (m.selectedIndex < firstVisible)
    firstVisible = m.selectedIndex;
  else if (m.selectedIndex >= firstVisible + 4)
    firstVisible = m.selectedIndex - 3;

  lcd.clear();

  for (uint8_t row = 0; row < 4; row++) {
    uint8_t idx = firstVisible + row;
    if (idx >= m.itemCount) break;

    lcd.setCursor(0, row);
    lcd.print(idx == m.selectedIndex
      ? (m.mode == MENU_MODE_EDIT ? "*" : ">")
      : " ");

    lcd.print(m.currentMenu[idx].label);

    if (m.currentMenu[idx].type == MENU_VALUE) {
      lcd.setCursor(14, row);
      //lcd.print(*m.currentMenu[idx].value);
      displayPrintValue(m.currentMenu[idx]);
    }
  }
}

static void displayPrintValue(const MenuItem& item) {
  if (item.value == nullptr) return;

  switch (item.format) {

    case MENU_FMT_NONE:
      lcd.print(*item.value);
      break;

    case MENU_FMT_SENSE:
      lcd.print(*item.value == 0 ? "Adel" : "Rev");
      break;

    case MENU_FMT_DEC1:
      lcd.print(*item.value / 10.0, 1);
      break;

    default:
      lcd.print(*item.value);
      break;
  }
}

void displayRenderStatus() {
  lcd.setCursor(0, 0);
  lcd.print("Estado Maquina");

  lcd.setCursor(0, 1);
  lcd.print("M1 Vel:");
  lcd.print(motor1_speed);

  lcd.setCursor(0, 2);
  lcd.print("M1 Acc:");
  lcd.print(motor1_accel);

  lcd.setCursor(0, 3);
  lcd.print("Menu: Click");
}

void displayClear() {
  lcd.clear();
}
