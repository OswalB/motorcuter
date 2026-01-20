#ifndef MENU_DATA_H
#define MENU_DATA_H

#include <Arduino.h>

enum MenuFormat {
  MENU_FMT_NONE,
  MENU_FMT_SENSE,
  MENU_FMT_DEC1
};

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

  MenuFormat format;

  void (*action)();
};

/* ====== VARIABLES REALES ====== */
extern int32_t motor1_speed;
extern int32_t motor1_accel;
extern int32_t motor1_sentido;

/* ====== MOTOR 2 ====== */
extern int32_t motor2_prg0_speed;
extern int32_t motor2_prg0_accel;

extern int32_t motor2_prg1_speed;
extern int32_t motor2_prg1_accel;

extern int32_t motor2_active_prg;

/* ====== MENÚ RAÍZ ====== */
extern const MenuItem mainMenu[];
extern const uint8_t mainMenuCount;

#endif
