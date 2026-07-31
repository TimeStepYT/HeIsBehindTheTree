#include "EggTree.hpp"
#include "Global.hpp"

#include <numbers>
#include <cmath>

using namespace geode::prelude;

EggTree* EggTree::create() {
    EggTree* ret = new EggTree();

    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool EggTree::init() {
    if (!CCNode::init())
        return false;

    this->setContentSize({180.f, 180.f});
    this->setAnchorPoint({0.5f, 0.5f});

    CCSprite* stump = CCSprite::create("stump.png"_spr);
    stump->setID("tree-stump");
    stump->setPosition({
        this->getContentWidth()  / 2.f + 13.156f, 
        this->getContentHeight() / 2.f + 30.f
    });
    stump->setAnchorPoint({0.5f, 0.5f});

    CCSprite* treeBack = CCSprite::create("treeBack.png"_spr);
    treeBack->setID("tree-back");
    treeBack->setPosition(this->m_backPos);
    treeBack->setAnchorPoint({0.5f, 0.5f});
    this->m_backLeaves = treeBack;
    
    CCSprite* treeFront = CCSprite::create("treeFront.png"_spr);
    treeFront->setID("tree-front");
    treeFront->setPosition(this->m_frontPos);
    treeFront->setAnchorPoint({0.5f, 0.5f});
    this->m_frontLeaves = treeFront;

    CCSprite* particleSprite = CCSprite::create("particle.png"_spr);
    particleSprite->setID("particle");
    particleSprite->setPosition(this->m_particlePos);
    particleSprite->setOpacity(0);
    this->m_particle = particleSprite;
    
    this->addChild(stump);
    this->addChild(treeBack);
    this->addChild(treeFront);
    this->addChild(particleSprite);
    this->addChild(CCNode::create());

    this->scheduleUpdate();

    return true;
}

// I hate this formula
float sinHelper(float timer, float duration, float completedArchesAmount, float amplitude) {
    return std::sin(
        timer * (static_cast<float>(std::numbers::pi) / (duration / completedArchesAmount))
        ) * amplitude;
}

void EggTree::update(float dt) {
    float const duration = 12.f;

    this->m_particleTimer += dt;
    this->m_animTimer += dt;
    if (this->m_animTimer > duration)
        this->m_animTimer -= duration;

    CCPoint backOffset{
        sinHelper(this->m_animTimer, duration, 4.f, 1.75f),
        sinHelper(this->m_animTimer, duration, 2.f, 1.75f)
    };
    
    CCPoint frontOffset{
        -sinHelper(this->m_animTimer, duration, 4.f, 1.5f),
        -sinHelper(this->m_animTimer, duration, 2.f, 1.5f)
    };

    this->m_backLeaves->setPosition(this->m_backPos + backOffset);
    this->m_frontLeaves->setPosition(this->m_frontPos + frontOffset);

    this->updateParticle();
}

void EggTree::resetParticle() {
    constexpr CCSize spawnArea{100.f, 42.f};
    
    // I just want a random position around the base position within the spawnArea
    float xOffset = (global::mt() % static_cast<int>(spawnArea.width * 1000.f)) / 1000.f - spawnArea.width / 2.f;
    float yOffset = (global::mt() % static_cast<int>(spawnArea.height * 1000.f)) / 1000.f - spawnArea.height / 2.f;

    this->m_particle->setPositionX(this->m_particlePos.x + xOffset);
    this->m_particle->setPositionY(this->m_particlePos.y + yOffset);
}

void EggTree::updateParticle() {
    float constexpr particleInterval = 2.f;
    float constexpr turningPoint = particleInterval * 0.2f;
    float constexpr fadeoutPoint = particleInterval * 0.5f;

    if (this->m_particleTimer > particleInterval) {
        this->m_particleTimer -= particleInterval;
        this->resetParticle();
    }

    float const timer = this->m_particleTimer;
    CCSprite* particle = this->m_particle;

    if (timer < turningPoint) {
        particle->setOpacity(255.f * (timer / turningPoint));
    }
    else {
        float const remainingFactor = (timer - turningPoint) / (fadeoutPoint - turningPoint);
        particle->setOpacity(std::fmax(0, 255.f - 255.f * remainingFactor));
    }

    float const timeFactor = timer / particleInterval;

    float const xVel = timeFactor * 0.125f;
    float const yOffset = timeFactor * -50.f;

    particle->setPositionX(particle->getPositionX() + xVel);
    particle->setPositionY(this->m_particlePos.y + yOffset);
}