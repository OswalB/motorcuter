#pragma once
#include <Arduino.h>

enum MotorDirection {
  MOTOR_DIR_CW,
  MOTOR_DIR_CCW
};

enum MotorMode {
  MOTOR_MODE_STOPPED,
  MOTOR_MODE_CONTINUOUS,
  MOTOR_MODE_TIMED,
  MOTOR_MODE_EVENT
};

struct MotorState {
  bool enabled;
  bool active;

  MotorMode mode;
  MotorDirection direction;

  uint16_t speed;
  uint16_t acceleration;

  uint32_t duration_ms;
  uint32_t start_timestamp_ms;
};

struct MachineState {
  MotorState motors[2];
};

extern MachineState machineState;

void machineStateInit();
void machineStateUpdate(uint32_t now_ms);
