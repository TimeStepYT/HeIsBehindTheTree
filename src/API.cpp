#define GEODE_DEFINE_EVENT_EXPORTS
#include "../api/API.hpp"

#include <algorithm>

using namespace geode::prelude;

template<typename T>
bool contains(std::span<std::string> list, T item) {
    return std::find(list.begin(), list.end(), item) != list.end();
}

namespace heisbehindthetree {
    std::string const receivedKey = "external-eggs-received";
    std::string const storedKey = "external-eggs-stored";
    std::string const customStoredKey = "external-eggs-stored-custom";

    Result<bool> receiveEgg(Mod* originMod) {
        auto const id = originMod->getID();

        auto receivedEggs = Mod::get()->getSavedValue<std::vector<std::string>>(receivedKey);

        if (originMod == Mod::get())
            return Err("You are not allowed to receive this egg externally");

        if (contains(receivedEggs, id)) {
            return Err("Egg was already received");
        }
        receivedEggs.push_back(id);

        Mod::get()->setSavedValue(receivedKey, receivedEggs);

        return Ok(true);
    }

    Result<bool> wasEggReceived(Mod* originMod) {
        auto receivedEggs = Mod::get()->getSavedValue<std::vector<std::string>>(receivedKey);
        auto const id = originMod->getID();

        if (originMod == Mod::get()) { // If for some reason you want to know if my egg was received
            return Ok(Mod::get()->getSavedValue<bool>("received-egg"));
        }

        bool const res = contains(receivedEggs, id);

        return Ok(res);
    }
    Result<bool> storeEgg(bool storeInCustomLocation, Mod* originMod) {
        auto const id = originMod->getID();

        auto storedEggs = Mod::get()->getSavedValue<std::vector<std::string>>(storedKey);
        
        if (originMod == Mod::get())
            return Err("You are not allowed to store this egg externally");

        if (contains(storedEggs, id)) {
            return Err("Egg was already stored");
        }
        storedEggs.push_back(id);
        
        if (storeInCustomLocation) {
            auto storedCustomEggs = Mod::get()->getSavedValue<std::vector<std::string>>(customStoredKey);
            storedCustomEggs.push_back(id);
            Mod::get()->setSavedValue(customStoredKey, storedCustomEggs);
        }

        Mod::get()->setSavedValue(storedKey, storedEggs);

        return Ok(true);
    }

    Result<bool> wasEggStored(Mod* originMod) {
        auto storedEggs = Mod::get()->getSavedValue<std::vector<std::string>>(storedKey);
        auto const id = originMod->getID();

        if (originMod == Mod::get()) { // If for some reason you want to know if my egg was stored
            return Ok(Mod::get()->getSavedValue<bool>("stored-egg"));
        }

        bool res = contains(storedEggs, id);

        return Ok(res);
    }
}