#pragma once

#include <Geode/Geode.hpp>
#include <Geode/loader/Dispatch.hpp>

#undef MY_MOD_ID
#define MY_MOD_ID "timestepyt.heisbehindthetree"

namespace heisbehindthetree {
    // Adds the egg from your mod to the list.
    //
    // The return value can be ignored, it just tells you if it was successful.
    inline geode::Result<bool> receiveEgg(geode::Mod* originMod = geode::Mod::get())
    GEODE_EVENT_EXPORT(&receiveEgg, (originMod));

    inline geode::Result<bool> wasEggReceived(geode::Mod* originMod = geode::Mod::get())
    GEODE_EVENT_EXPORT(&wasEggReceived, (originMod));
    
    // Adds the egg from your mod to the list.
    //
    // The return value can be ignored, it just tells you if it was successful.
    inline geode::Result<bool> storeEgg(bool storeInCustomLocation = false, geode::Mod* originMod = geode::Mod::get())
    GEODE_EVENT_EXPORT(&storeEgg, (storeInCustomLocation, originMod));
    
    inline geode::Result<bool> wasEggStored(geode::Mod* originMod = geode::Mod::get())
    GEODE_EVENT_EXPORT(&wasEggStored, (originMod));
}
