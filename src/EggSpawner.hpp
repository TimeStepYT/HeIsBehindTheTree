#pragma once

#include <Geode/Geode.hpp>

class EggSpawner : public cocos2d::CCNode {
protected:
    bool init() override;
public:
    static EggSpawner* create();

    void spawnEggs(unsigned int count);
};