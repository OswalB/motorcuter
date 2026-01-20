#ifndef MENU_DATA_H
#define MENU_DATA_H

#include <Arduino.h>

enum MenuItemType {
  MENU_SUBMENU,
  MENU_VALUE,
  MENU_ACTION
};

struct MenuItem {
  const char* label;
  MenuItemType type;

  const MenuItem* children;
  uint8_t childrenCount;

  int32_t* value;
  int32_t min;
  int32_t max;
  int32_t step;

  void (*action)();
};

/* ====== VARIABLES REALES ====== */
extern int32_t motor1_speed;
extern int32_t motor1_accel;
extern int32_t motor1_sentido;

/* ====== MENÚ RAÍZ ====== */
extern const MenuItem mainMenu[];
extern const uint8_t mainMenuCount;

#endif
