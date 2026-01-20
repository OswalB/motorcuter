#ifndef MENU_H
#define MENU_H

#include "menu_data.h"
#include "menu_events.h"



enum MenuMode {
  MENU_MODE_NAVIGATE,
  MENU_MODE_EDIT
};

/*struct MenuContext {
  const MenuItem* currentMenu;
  uint8_t itemCount;
  uint8_t selectedIndex;
  MenuMode mode;

  const MenuItem* parentMenu;
  uint8_t parentCount;
};*/

#define MENU_STACK_MAX 6

struct MenuContext {
  const MenuItem* currentMenu;
  uint8_t itemCount;
  uint8_t selectedIndex;
  MenuMode mode;

  const MenuItem* menuStack[MENU_STACK_MAX];
  uint8_t indexStack[MENU_STACK_MAX];
  uint8_t countStack[MENU_STACK_MAX];
  uint8_t depth;
};

void menuInit();
void menuHandleEvent(MenuEvent event);

const MenuContext& menuGetContext();

#endif
