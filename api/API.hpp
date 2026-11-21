#pragma once

#include <Geode/Geode.hpp>
#include <Geode/loader/EventExport.hpp>

#undef MY_MOD_ID
#define MY_MOD_ID "timestepyt.heisbehindthetree"

namespace heisbehindthetree {
    // Adds the egg from your mod to the list.
    //
    // The return value can be ignored, it just tells you if it was successful.
    GEODE_EVENT_EXPORT(geode::Result<bool>, receiveEgg, (geode::Mod* originMod = geode::Mod::get()), (originMod));

    GEODE_EVENT_EXPORT(geode::Result<bool>, wasEggReceived, (geode::Mod* originMod = geode::Mod::get()), (originMod));
    
    // Adds the egg from your mod to the list.
    //
    // The return value can be ignored, it just tells you if it was successful.
    GEODE_EVENT_EXPORT(geode::Result<bool>, storeEgg, (bool storeInCustomLocation = false, geode::Mod* originMod = geode::Mod::get()), (storeInCustomLocation, originMod));
    
    GEODE_EVENT_EXPORT(geode::Result<bool>, wasEggStored, (geode::Mod* originMod = geode::Mod::get()), (originMod));
}
