#include "storage.h"
#include <EEPROM.h>

/* ================= CONFIG EN RAM ================= */

static MachineConfig config;

/* ================= DEFAULTS DE FÁBRICA ================= */

static const MachineConfig factoryDefaults = {
  .magic   = CONFIG_MAGIC,
  .version = CONFIG_VERSION,
  .rpm     = 120,
  .sentido = false,
  .tiempo  = 30
};

/* ================= FUNCIONES INTERNAS ================= */

static void loadFactoryDefaults() {
  config = factoryDefaults;
}

/* ================= API ================= */

void storageInit() {
  EEPROM.get(STORAGE_ADDR_CONFIG, config);

  // EEPROM vacía o no válida
  if (config.magic != CONFIG_MAGIC) {
    loadFactoryDefaults();
    EEPROM.put(STORAGE_ADDR_CONFIG, config);
    return;
  }

  // Versión incompatible
  if (config.version != CONFIG_VERSION) {
    // Aquí luego puedes implementar migraciones
    loadFactoryDefaults();
    EEPROM.put(STORAGE_ADDR_CONFIG, config);
    return;
  }

  // Si llega aquí → datos válidos
}

void storageSave() {
  EEPROM.put(STORAGE_ADDR_CONFIG, config);
}

void storageFactoryReset() {
  loadFactoryDefaults();
  EEPROM.put(STORAGE_ADDR_CONFIG, config);
}

MachineConfig* storageGet() {
  return &config;
}
