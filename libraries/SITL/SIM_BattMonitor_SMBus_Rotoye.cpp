#include "SIM_BattMonitor_SMBus_Rotoye.h"

SITL::Rotoye::Rotoye() :
    SIM_BattMonitor_SMBus_Generic()
{
    add_register("External Temperature", SMBusBattRotoyeDevReg::TEMP_EXT, O_RDONLY);

    set_register(SMBusBattRotoyeDevReg::SERIAL, (uint16_t)39);
}

void SITL::Rotoye::update(const class Aircraft &aircraft)
{
    SIM_BattMonitor_SMBus_Generic::update(aircraft);

    const uint32_t now = AP_HAL::millis();
    if (now - last_temperature_update_ms > 1000) {
        last_temperature_update_ms = now;
        set_register(SMBusBattRotoyeDevReg::TEMP_EXT, int16_t(be16toh(word[SMBusBattRotoyeDevReg::TEMP]) + 100));  // it's a little warmer inside.... (10 degrees here)
    }
}