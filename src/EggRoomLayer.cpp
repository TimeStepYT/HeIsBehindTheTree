#include "EggRoomLayer.hpp"
#include "EggTree.hpp"

using namespace geode::prelude;

EggRoomLayer* EggRoomLayer::create() {
    auto ret = new EggRoomLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

CCScene* EggRoomLayer::scene() {
    auto layer = EggRoomLayer::create();
    auto scene = CCScene::create();
    layer->setID("main-layer");
    scene->addChild(layer);
    return scene;
}

bool EggRoomLayer::init() {
    if (!CCLayer::init())
        return false;

    geode::addBackButton(this);

    this->setMouseEnabled(true);
    this->setTouchEnabled(true);
    this->setKeyboardEnabled(true);
    this->setKeypadEnabled(true);

    auto floorCircle = CCSprite::create("floorCircle.png"_spr);
    floorCircle->setPosition(this->getContentSize() / 2.f);
    floorCircle->setID("floor-circle");

    auto floorSquare = CCLayerColor::create();
    floorSquare->setColor({98, 43, 98});
    floorSquare->setOpacity(255);
    floorSquare->setAnchorPoint({0.5f, 1.f});
    floorSquare->ignoreAnchorPointForPosition(false);
    floorSquare->setPosition(floorCircle->getPosition());
    floorSquare->setContentWidth(60.f);
    floorSquare->setContentHeight(this->getContentHeight() / 2);
    floorSquare->setID("floor-square");

    auto tree = EggTree::create();
    tree->setPosition(floorCircle->getPosition());
    tree->setID("tree");

    this->addChild(floorCircle);
    this->addChild(floorSquare);
    this->addChild(tree);

    return true;
}