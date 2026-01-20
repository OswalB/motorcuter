#include "menu_data.h"

int32_t motor1_speed = 100;
int32_t motor1_accel = 50;
int32_t motor1_sentido = 0; // 0 = Adelante, 1 = Reversa

const MenuItem motor1Menu[] = {
  {
    "Velocidad",
    MENU_VALUE,
    nullptr, 0,
    &motor1_speed, 0, 1000, 10,
    nullptr
  },
  {
    "Aceleracion",
    MENU_VALUE,
    nullptr, 0,
    &motor1_accel, 0, 500, 5,
    nullptr
  },
  {
    "Sentido",
    MENU_VALUE,
    nullptr, 0,
    &motor1_sentido, 0, 1, 1,
    nullptr
  }
};

const MenuItem mainMenu[] = {
  {
    "Motor 1",
    MENU_SUBMENU,
    motor1Menu, 3,
    nullptr, 0, 0, 0,
    nullptr
  }
};

const uint8_t mainMenuCount = 1;
