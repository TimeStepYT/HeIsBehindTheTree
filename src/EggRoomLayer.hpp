#pragma once

#include <Geode/Geode.hpp>

class EggRoomLayer : public cocos2d::CCLayer {
private:
    bool init();

public:
    static EggRoomLayer* create();
    static cocos2d::CCScene* scene();
};