#include "menu.h"

static MenuContext menu;

void menuInit() {
  menu.currentMenu = mainMenu;
  menu.itemCount = mainMenuCount;
  menu.selectedIndex = 0;
  menu.mode = MENU_MODE_NAVIGATE;
  menu.parentMenu = nullptr;
}

const MenuContext& menuGetContext() {
  return menu;
}

void menuHandleEvent(MenuEvent event) {
  if (event == MENU_EVENT_NONE) return;

  const MenuItem* item = &menu.currentMenu[menu.selectedIndex];

  if (menu.mode == MENU_MODE_NAVIGATE) {
    if (event == MENU_EVENT_UP && menu.selectedIndex > 0)
      menu.selectedIndex--;

    if (event == MENU_EVENT_DOWN && menu.selectedIndex < menu.itemCount - 1)
      menu.selectedIndex++;

    if (event == MENU_EVENT_CLICK) {
      if (item->type == MENU_SUBMENU) {
        menu.parentMenu = menu.currentMenu;
        menu.parentCount = menu.itemCount;
        menu.currentMenu = item->children;
        menu.itemCount = item->childrenCount;
        menu.selectedIndex = 0;
      }
      else if (item->type == MENU_VALUE) {
        menu.mode = MENU_MODE_EDIT;
      }
    }

    if (event == MENU_EVENT_BACK && menu.parentMenu) {
      menu.currentMenu = menu.parentMenu;
      menu.itemCount = menu.parentCount;
      menu.parentMenu = nullptr;
      menu.selectedIndex = 0;
    }
  }
  else {
    if (event == MENU_EVENT_UP && *item->value + item->step <= item->max)
      *item->value += item->step;

    if (event == MENU_EVENT_DOWN && *item->value - item->step >= item->min)
      *item->value -= item->step;

    if (event == MENU_EVENT_CLICK)
      menu.mode = MENU_MODE_NAVIGATE;
  }
}
