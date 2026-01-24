#include <Arduino.h>
#include "serial_if.h"
#include "machine_state.h"

/* ===== Forward declaration ===== */
static void handleCommand(const String& cmd);

static String buffer;

void serialInit() {
  Serial.begin(115200);
}

void serialUpdate() {
  while (Serial.available()) {
    char c = Serial.read();
    Serial.write(c);   // eco
    if (c == '\n') {
      buffer.trim();
      handleCommand(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }
}

static void handleCommand(const String& cmd) {
  if (cmd == "start") {
    //machineStart();
    digitalWrite(13,HIGH);
  }
  else if (cmd == "stop") {
   // machineStop();
   digitalWrite(13,LOW);
  }
  else if (cmd.startsWith("motor1 speed ")) {
    int v = cmd.substring(13).toInt();
    //machineSetMotorSpeed(1, v);
  }
  else if (cmd.startsWith("motor1 dir ")) {
    String d = cmd.substring(11);
    //machineSetMotorDir(1, d == "cw");
  }
}
