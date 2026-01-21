#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H

#include <stdint.h>

struct MachineState {
  bool motor1Running;
  bool motor2Running;
  uint8_t motor2PrgActive;
};

extern MachineState machineState;

void machineStateInit();

#endif
