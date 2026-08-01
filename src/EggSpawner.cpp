#include "EggSpawner.hpp"
#include "Global.hpp"

using namespace geode::prelude;

EggSpawner* EggSpawner::create() {
    EggSpawner* ret = new EggSpawner();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool EggSpawner::init() {
    if (!CCNode::create())
        return false;
    
    return true;
}

void EggSpawner::spawnEggs(unsigned int count) {
    log::debug("Spawning eggs: {}", count);
    for (int i = 0; i < count; ++i) {
        int maxX = this->getContentWidth() * 100.f;
        int maxY = this->getContentHeight() * 100.f;

        if (maxX == 0 && maxY == 0)
            log::warn("The size is 0, please call spawnEggs() AFTER setting the size!");

        if (maxX == 0)
            maxX = 1;
        if (maxY == 0)
            maxY = 1;

        float randomX = (global::mt() % maxX) / 100.f;
        float randomY = (global::mt() % maxY) / 100.f;

        log::info("{} {}", randomX, randomY);

        CCSprite* eggSprite = CCSprite::create("egg.png"_spr);
        eggSprite->setPositionX(randomX);
        eggSprite->setPositionY(randomY);

        this->addChild(eggSprite);
    }
}