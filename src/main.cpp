#include <Arduino.h>

#include <encoder.h>
#include <menu.h>
#include <display.h>
#include "machine_state.h"

enum UiScreen
{
  UI_SCREEN_STATUS,
  UI_SCREEN_SETTINGS
};

static UiScreen currentScreen = UI_SCREEN_STATUS;

void setup()
{
  encoderInit();
  menuInit();
  displayInit();
  displayRenderMenu();
  machineStateInit();
}

void loop()
{
  MenuEvent event = encoderGetEvent();

  /* ================== STATUS ================== */
  if (currentScreen == UI_SCREEN_STATUS)
  {

    if (event == MENU_EVENT_CLICK)
    {
      currentScreen = UI_SCREEN_SETTINGS;
      displayClear();
      displayRenderMenu();
    }
    else
    {
      displayRenderStatus();
    }
  }

  /* ================== SETTINGS ================== */
  else
  {

    if (event == MENU_EVENT_BACK)
    {
      currentScreen = UI_SCREEN_STATUS;
      displayClear();
    }
    else if (event != MENU_EVENT_NONE)
  {
    menuHandleEvent(event);
    displayRenderMenu();
  }
  }
}