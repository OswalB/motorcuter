//#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Bounce2.h>
#include "encoder.h"

// 🔌 Pines (solo aquí)
#define ENC_A 2   // CLK
#define ENC_B 3   // DT
#define ENC_BTN  4   // Botón

// 🔧 Objetos internos (solo visibles aquí)
static RotaryEncoder encoder(
  ENC_A,
  ENC_B,
  RotaryEncoder::LatchMode::FOUR3
);

//static Bounce button = Bounce();
Bounce button;

static long lastPos = 0;
static unsigned long pressTime = 0;
static bool pressed = false;

/*void encoderInit() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  button.attach(ENC_SW);
  button.interval(5);   // 5 ms es suficiente
}*/

void encoderInit() {
  pinMode(ENC_BTN, INPUT_PULLUP);
  encoder.setPosition(0);
  button.attach(ENC_BTN);
  button.interval(5);
}


/*void encoderUpdate() {
  encoder.tick();   
  button.update();
}

long encoderGetValue() {
  return encoder.getPosition();
}

bool encoderButtonPressed() {
  return button.fell(); // true SOLO en el flanco
}
*/

MenuEvent encoderGetEvent() {
  encoder.tick();
  long pos = encoder.getPosition();

  if (pos != lastPos) {
    MenuEvent e = pos > lastPos ? MENU_EVENT_DOWN : MENU_EVENT_UP;
    lastPos = pos;
    return e;
  }

  button.update();

  if (button.fell()) {
    pressTime = millis();
    pressed = true;
  }

  if (button.rose() && pressed) {
    pressed = false;
    return (millis() - pressTime > 800)
      ? MENU_EVENT_BACK
      : MENU_EVENT_CLICK;
  }

  return MENU_EVENT_NONE;
}