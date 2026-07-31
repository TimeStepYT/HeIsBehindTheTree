#pragma once

#include <Geode/Geode.hpp>

class EggRoomLayer : public cocos2d::CCLayer {
private:
    bool init() override;
    void onExit() override;
    void keyBackClicked() override;

public:
    static EggRoomLayer* create();
    static cocos2d::CCScene* scene();
};