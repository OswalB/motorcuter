#include "machine_state.h"

MachineState machineState;

void machineStateInit() {
  for (int i = 0; i < 2; i++) {
    machineState.motors[i] = {
      .enabled = true,
      .active = false,
      .mode = MOTOR_MODE_STOPPED,
      .direction = MOTOR_DIR_CW,
      .speed = 1000,
      .acceleration = 500,
      .duration_ms = 0,
      .start_timestamp_ms = 0
    };
  }
}

void machineStateUpdate(uint32_t now_ms) {
  for (int i = 0; i < 2; i++) {
    MotorState& m = machineState.motors[i];

    // Seguridad primero
    if (!m.enabled) {
      m.active = false;
      m.mode = MOTOR_MODE_STOPPED;
      continue;
    }

    // Evaluar modo
    if (m.mode == MOTOR_MODE_TIMED && m.active) {
      if (now_ms - m.start_timestamp_ms >= m.duration_ms) {
        m.active = false;
        m.mode = MOTOR_MODE_STOPPED;
      }
    }
  }
}
