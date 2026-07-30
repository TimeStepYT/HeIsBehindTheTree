#include <Geode/Geode.hpp>

#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class $modify(ManCreatorLayer, CreatorLayer) {
    void onTreasureRoom(CCObject* sender) {
        
        CreatorLayer::onTreasureRoom(sender);
    }
};