#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
#include <Bounce2.h>


#define LED_PIN 13

#define ENC_A 8   // CLK
#define ENC_B 9   // DT
#define ENC_SW 10 // Botón

LiquidCrystal_I2C lcd(0x27, 20, 4);

RotaryEncoder encoder(ENC_A, ENC_B);
Bounce button = Bounce();
long lastPos = 0;

void setup() {

   Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  lcd.init();        // Inicializa LCD
  lcd.backlight();  // Enciende luz de fondo

  lcd.setCursor(0, 0);
  lcd.print("Proyecto Arduino");
  lcd.setCursor(0, 1);
  lcd.print("LCD 20x4 I2C");

   pinMode(ENC_SW, INPUT_PULLUP);
  button.attach(ENC_SW);
  button.interval(5);

  Serial.println("Encoder test start");
}

void loop() {

encoder.tick();
  button.update();

  long newPos = encoder.getPosition();
  if (newPos != lastPos) {
    Serial.print("Position: ");
    Serial.println(newPos);
    lastPos = newPos;
  }

  if (button.fell()) {
    Serial.println("Button pressed");
  }

  
}
