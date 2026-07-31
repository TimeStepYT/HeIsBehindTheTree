#include <Geode/Geode.hpp>

#include <Geode/modify/CreatorLayer.hpp>

#include "EggRoomLayer.hpp"
#include "Global.hpp"

using namespace geode::prelude;

class $modify(ManCreatorLayer, CreatorLayer) {
    // You're here to know how to activate it, aren't you... cheater.
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