#pragma once

#include <Geode/Geode.hpp>

class EggRoomLayer : public cocos2d::CCLayer {
protected:
    int m_buttonInteractCounter = 0;

    bool init() override;
    void onExit() override;
    void keyBackClicked() override;

    void receiveEgg();
    void showAlert(std::string const& text);
    void showDefaultMessage();
    void eggSequence();
    void dialogButtonClicked(cocos2d::CCMenuItem* sender);

public:
    static EggRoomLayer* create();
    static cocos2d::CCScene* scene();
};