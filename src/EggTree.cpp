#include "EggTree.hpp"
#include <numbers>

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

    auto stump = CCSprite::create("stump.png"_spr);
    stump->setID("tree-stump");
    stump->setPosition({
        this->getContentWidth()  / 2.f + 13.156f, 
        this->getContentHeight() / 2.f + 30.f
    });
    stump->setAnchorPoint({0.5f, 0.5f});
    stump->setScale(5.5f);
    stump->getTexture()->setAliasTexParameters();

    auto treeBack = CCSprite::create("treeBack.png"_spr);
    treeBack->setID("tree-back");
    treeBack->setPosition(this->m_backPos);
    treeBack->setAnchorPoint({0.5f, 0.5f});
    this->m_backLeaves = treeBack;
    
    auto treeFront = CCSprite::create("treeFront.png"_spr);
    treeFront->setID("tree-front");
    treeFront->setPosition(this->m_frontPos);
    treeFront->setAnchorPoint({0.5f, 0.5f});
    this->m_frontLeaves = treeFront;
    
    this->addChild(stump);
    this->addChild(treeBack);
    this->addChild(treeFront);

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

    this->m_animTimer += dt;
    if (this->m_animTimer > duration)
        this->m_animTimer -= duration;

    CCPoint backOffset{
        sinHelper(this->m_animTimer, duration, 4.f, 3.f),
        sinHelper(this->m_animTimer, duration, 2.f, 2.5f)
    };
    
    CCPoint frontOffset{
        -sinHelper(this->m_animTimer, duration, 4.f, 1.5f),
        -sinHelper(this->m_animTimer, duration, 2.f, 1.5f)
    };

    this->m_backLeaves->setPosition(this->m_backPos + backOffset);
    this->m_frontLeaves->setPosition(this->m_frontPos + frontOffset);
}