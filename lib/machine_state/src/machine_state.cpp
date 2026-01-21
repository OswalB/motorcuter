#include "machine_state.h"

MachineState machineState;

void machineStateInit() {
  machineState.motor1Running = false;
  machineState.motor2Running = false;
  machineState.motor2PrgActive = 0;
}