#include <Arduino.h>

#include <encoder.h>
#include <menu.h>
#include <display.h>
#include "machine_state.h"
#include "serial_if.h"
#include "storage.h"

enum UiScreen
{
  UI_SCREEN_STATUS,
  UI_SCREEN_SETTINGS
};

static UiScreen currentScreen = UI_SCREEN_STATUS;

void setup()
{ 
  pinMode(13,OUTPUT);
  serialInit();
  Serial.println("HELLO World");
  encoderInit();
  menuInit();
  displayInit();
  displayRenderMenu();
  machineStateInit();
  storageInit();

  //test datos eeprom

   MachineConfig* cfg = storageGet();

  Serial.println("CONFIG ACTUAL:");
  Serial.print("RPM: ");
  Serial.println(cfg->rpm);
  Serial.print("Sentido: ");
  Serial.println(cfg->sentido);
  Serial.print("Tiempo: ");
  Serial.println(cfg->tiempo);

  // Simular cambio del usuario
  //cfg->rpm = 201;
  cfg->sentido = true;

  //storageSave();

   

  Serial.println("CONFIG actualizada:");
  Serial.print("RPM: ");
  Serial.println(cfg->rpm);
  Serial.print("Sentido: ");
  Serial.println(cfg->sentido);
  Serial.print("Tiempo: ");
  Serial.println(cfg->tiempo);
}

void loop()
{
  serialUpdate();

   uint32_t now = millis();

  machineStateUpdate(now);  


  
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