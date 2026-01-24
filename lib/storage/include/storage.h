#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>

/* ================= CONFIGURACIÓN ================= */

#define STORAGE_ADDR_CONFIG  0
#define CONFIG_MAGIC         0xA5
#define CONFIG_VERSION       1

/* ================= ESTRUCTURA ================= */

struct MachineConfig {
  uint8_t  magic;     // Identificador de datos válidos
  uint8_t  version;   // Versión de la estructura
  uint16_t rpm;       // Ejemplo: velocidad motor
  bool     sentido;   // Ejemplo: giro
  uint16_t tiempo;    // Ejemplo: tiempo proceso
};

/* ================= API ================= */

void storageInit();          // Llamar en setup()
void storageSave();          // Guardar configuración actual
void storageFactoryReset();  // Restaurar valores de fábrica

MachineConfig* storageGet(); // Acceso a la config en RAM

#endif
