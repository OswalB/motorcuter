#include "menu_data.h"

int32_t motor1_speed = 100;
int32_t motor1_accel = 50;
int32_t motor1_sentido = 0; // 0 = Adelante, 1 = Reversa

int32_t motor2_active_prg = 0; // PRG0 por defecto

int32_t motor2_prg0_speed = 800;
int32_t motor2_prg0_accel = 40;

int32_t motor2_prg1_speed = 1200;
int32_t motor2_prg1_accel = 60;


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

const MenuItem motor2_prg0_Menu[] = {
  {
    "Velocidad",
    MENU_VALUE,
    nullptr, 0,
    &motor2_prg0_speed, 0, 1500, 10,
    nullptr
  },
  {
    "Aceleracion",
    MENU_VALUE,
    nullptr, 0,
    &motor2_prg0_accel, 0, 500, 5,
    nullptr
  }
};

const MenuItem motor2_prg1_Menu[] = {
  {
    "Velocidad",
    MENU_VALUE,
    nullptr, 0,
    &motor2_prg1_speed, 0, 1500, 10,
    nullptr
  },
  {
    "Aceleracion",
    MENU_VALUE,
    nullptr, 0,
    &motor2_prg1_accel, 0, 500, 5,
    nullptr
  }
};

//  menu motor2

const MenuItem motor2Menu[] = {
  {
    "Programa",
    MENU_VALUE,
    nullptr, 0,
    &motor2_active_prg, 0, 1, 1,
    nullptr
  },
  {
    "PRG0",
    MENU_SUBMENU,
    motor2_prg0_Menu, 2,
    nullptr, 0, 0, 0,
    nullptr
  },
  {
    "PRG1",
    MENU_SUBMENU,
    motor2_prg1_Menu, 2,
    nullptr, 0, 0, 0,
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
  },
  {
    "Motor 2",
    MENU_SUBMENU,
    motor2Menu, 3,
    nullptr, 0, 0, 0,
    nullptr
  }
};

const uint8_t mainMenuCount = 2;
