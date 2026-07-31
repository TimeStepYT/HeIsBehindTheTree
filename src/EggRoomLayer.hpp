#pragma once

#include <Geode/Geode.hpp>

class EggRoomLayer : public cocos2d::CCLayer {
private:
    bool init() override;
    void onExit() override;
    void keyBackClicked() override;

    void dialogButtonClicked(cocos2d::CCMenuItem* sender);

public:
    static EggRoomLayer* create();
    static cocos2d::CCScene* scene();
};