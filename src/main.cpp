#include <Arduino.h>

#include <encoder.h>
#include <menu.h>
#include <display.h>


/*void setup() {
  Serial.begin(115200);
  encoderInit();
  displayInit();

  Serial.println("display test start 0");
}

void loop() {
   encoderUpdate();

  static long lastValue  = 0;
  long value = encoderGetValue();

  if (value != lastValue ) {
    Serial.print("Value: ");
    Serial.println(value);
    displayPrintValue(value);
    lastValue = value;
  }

  if (encoderButtonPressed()) {
    displayPrintMessage("Boton", "Presionado");
    Serial.println("BUTTON CLICK");
  }
}*/

void setup() {
  encoderInit();
  menuInit();
  displayInit();
  displayRenderMenu();
}

void loop() {
  MenuEvent event = encoderGetEvent();

  if (event != MENU_EVENT_NONE) {
    menuHandleEvent(event);
    displayRenderMenu();
  }
}