#include <Geode/Geode.hpp>

#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/SecretLayer2.hpp>

#include "EggRoomLayer.hpp"
#include "Global.hpp"

using namespace geode::prelude;

class $modify(ManCreatorLayer, CreatorLayer) {
    void onTreasureRoom(CCObject* sender) {
        bool toEggRoom = (global::mt() % 100) < 2; // 2% chance
        //toEggRoom = true;
        if (!toEggRoom)
            return CreatorLayer::onTreasureRoom(sender);

        CCDirector* director = CCDirector::get();
        CCScene* scene = EggRoomLayer::scene();

        director->pushScene(CCTransitionFade::create(3.f, scene));
    }
};

class $modify(ManVaultLayer, SecretLayer2) {
    void onSubmit(CCObject* sender) {
        auto const getSavedValue = +[](std::string_view key){
            return Mod::get()->getSavedValue<bool>(key);
        };

        if (!getSavedValue("received-egg") || getSavedValue("stored-egg")) {
            SecretLayer2::onSubmit(sender);
            return;
        }

        std::string searchString = this->m_searchInput->getString();
        
        for (size_t i = 0; i < searchString.size(); ++i) {
            searchString[i] = std::tolower(searchString[i]);
        }

        if (searchString == "egg") {
            SecretLayer2::updateMessageLabel("What am I supposed to do with this Egg?");
            SecretLayer2::updateSearchLabel("");
            this->m_messageLabel->setColor(ccc3(0, 255, 0));
            FMODAudioEngine::sharedEngine()->playEffect("snd_egg.wav"_spr);
            Mod::get()->setSavedValue<bool>("stored-egg", true);
            return;
        }

        SecretLayer2::onSubmit(sender);
    }
};