#pragma once

#include <Geode/Geode.hpp>

class EggTree : public cocos2d::CCNode {
private:
    cocos2d::CCPoint const m_backPos{101.f, 113.f};
    cocos2d::CCPoint const m_frontPos{103.f, 116.f};

    cocos2d::CCSprite* m_backLeaves = nullptr;
    cocos2d::CCSprite* m_frontLeaves = nullptr;

    float m_animTimer{};

    bool init() override;
    void update(float dt) override;
    
public:
    static EggTree* create();

};