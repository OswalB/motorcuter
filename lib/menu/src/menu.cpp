#include "menu.h"

static MenuContext menu;

/*void menuInit() {
  menu.currentMenu = mainMenu;
  menu.itemCount = mainMenuCount;
  menu.selectedIndex = 0;
  menu.mode = MENU_MODE_NAVIGATE;
  menu.parentMenu = nullptr;
}*/

/* ===== Inicialización ===== */
void menuInit() {
  menu.currentMenu = mainMenu;
  menu.itemCount = mainMenuCount;
  menu.selectedIndex = 0;
  menu.mode = MENU_MODE_NAVIGATE;

  menu.depth = 0;
}

const MenuContext& menuGetContext() {
  return menu;
}

/* 
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
}*/


void menuHandleEvent(MenuEvent event) {
  if (event == MENU_EVENT_NONE) return;

  const MenuItem* item = &menu.currentMenu[menu.selectedIndex];

  /* ================== MODO NAVEGACIÓN ================== */
  if (menu.mode == MENU_MODE_NAVIGATE) {

    if (event == MENU_EVENT_UP && menu.selectedIndex > 0)
      menu.selectedIndex--;

    if (event == MENU_EVENT_DOWN && menu.selectedIndex < menu.itemCount - 1)
      menu.selectedIndex++;

    if (event == MENU_EVENT_CLICK) {

      /* ---- Entrar a submenú ---- */
      if (item->type == MENU_SUBMENU && item->children) {

        if (menu.depth < MENU_STACK_MAX) {
          menu.menuStack[menu.depth] = menu.currentMenu;
          menu.indexStack[menu.depth] = menu.selectedIndex;
          menu.countStack[menu.depth] = menu.itemCount;
          menu.depth++;
        }

        menu.currentMenu = item->children;
        menu.itemCount = item->childrenCount;
        menu.selectedIndex = 0;
      }

      /* ---- Editar valor ---- */
      else if (item->type == MENU_VALUE) {
        menu.mode = MENU_MODE_EDIT;
      }

      /* ---- Acción ---- */
      else if (item->type == MENU_ACTION && item->action) {
        item->action();
      }
    }

    /* ---- Retroceder ---- */
    if (event == MENU_EVENT_BACK && menu.depth > 0) {
      menu.depth--;

      menu.currentMenu = menu.menuStack[menu.depth];
      menu.selectedIndex = menu.indexStack[menu.depth];
      menu.itemCount = menu.countStack[menu.depth];
    }
  }

  /* ================== MODO EDICIÓN ================== */
  else {
    if (item->type != MENU_VALUE || !item->value) return;

    if (event == MENU_EVENT_UP && *item->value + item->step <= item->max)
      *item->value += item->step;

    if (event == MENU_EVENT_DOWN && *item->value - item->step >= item->min)
      *item->value -= item->step;

    if (event == MENU_EVENT_CLICK)
      menu.mode = MENU_MODE_NAVIGATE;
  }
}