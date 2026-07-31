#pragma once

#include <Geode/Geode.hpp>

class EggTree : public cocos2d::CCNode {
protected:
    cocos2d::CCPoint const m_backPos{101.f, 113.f};
    cocos2d::CCPoint const m_frontPos{103.f, 116.f};
    cocos2d::CCPoint const m_particlePos{105.f, 125.f};

    cocos2d::CCSprite* m_backLeaves = nullptr;
    cocos2d::CCSprite* m_frontLeaves = nullptr;
    cocos2d::CCSprite* m_particle = nullptr;

    float m_animTimer{};
    float m_particleTimer{};

    bool init() override;
    void update(float dt) override;
    void resetParticle();
    void updateParticle();
public:
    static EggTree* create();

};