#include <LiquidCrystal_I2C.h>
#include "display.h"
#include "menu.h"
#include "machine_state.h"
#include "display_fmt.h"

#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

static LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
static uint8_t firstVisible = 0;
static void displayPrintValue(const MenuItem &item);

void displayInit()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void displaySetCursor(uint8_t col, uint8_t row) {
  lcd.setCursor(col, row);
}

void displayPrint(const char* txt) {
  lcd.print(txt);
}

void displayPrintChar(char c) {
  lcd.print(c);
}

void displayRenderMenu()
{
  const MenuContext &m = menuGetContext();

  if (m.selectedIndex < firstVisible)
    firstVisible = m.selectedIndex;
  else if (m.selectedIndex >= firstVisible + 4)
    firstVisible = m.selectedIndex - 3;

  lcd.clear();

  for (uint8_t row = 0; row < 4; row++)
  {
    uint8_t idx = firstVisible + row;
    if (idx >= m.itemCount)
      break;

    lcd.setCursor(0, row);
    lcd.print(idx == m.selectedIndex
                  ? (m.mode == MENU_MODE_EDIT ? "*" : ">")
                  : " ");

    lcd.print(m.currentMenu[idx].label);

    if (m.currentMenu[idx].type == MENU_VALUE)
    {
      lcd.setCursor(14, row);
      // lcd.print(*m.currentMenu[idx].value);
      displayPrintValue(m.currentMenu[idx]);
    }
  }
}

static void displayPrintValue(const MenuItem &item)
{
  if (item.value == nullptr)
    return;

  switch (item.format)
  {

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

void displayRenderStatus()
{
  //lcdFmtInt(0, 0, 0,20, ALIGN_RIGHT, FMT_MODE);    
  ///lcdFmtInt(0, 1, 0, 20, ALIGN_RIGHT, FMT_BOOL);    
  lcdFmtInt(0, 0, 4567, 20, ALIGN_LEFT,FMT_DEC_1);
  //lcdFmtInt(0, 3, 4567, 20, ALIGN_LEFT,FMT_DEC_2);
lcdFmtInt(0, 1, 125, 15, ALIGN_LEFT, FMT_RPM);      // "125 RPM"
lcdFmtInt(0, 2, 153, 15, ALIGN_RIGHT, FMT_DEC1_S);  // "15.3 s"
lcdFmtInt(0, 3, 250, 15, ALIGN_RIGHT, FMT_DEC1_MS); // "25.0 ms"
  
}

void displayClear()
{
  lcd.clear();
}
