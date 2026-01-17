#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Bounce2.h>
#include "encoder.h"

// 🔌 Pines (solo aquí)
#define ENC_A 2   // CLK
#define ENC_B 3   // DT
#define ENC_SW  4   // Botón

// 🔧 Objetos internos (solo visibles aquí)
static RotaryEncoder encoder(
  ENC_A,
  ENC_B,
  RotaryEncoder::LatchMode::FOUR3
);

static Bounce button = Bounce();

void encoderInit() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  button.attach(ENC_SW);
  button.interval(5);   // 5 ms es suficiente
}

void encoderUpdate() {
  encoder.tick();   
  button.update();
}

long encoderGetValue() {
  return encoder.getPosition();
}

bool encoderButtonPressed() {
  return button.fell(); // true SOLO en el flanco
}
