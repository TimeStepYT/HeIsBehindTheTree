#include "EggRoomLayer.hpp"
#include "EggTree.hpp"

using namespace geode::prelude;

EggRoomLayer* EggRoomLayer::create() {
    EggRoomLayer* ret = new EggRoomLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

CCScene* EggRoomLayer::scene() {
    EggRoomLayer* layer = EggRoomLayer::create();
    CCScene* scene = CCScene::create();
    layer->setID("main-layer");
    scene->addChild(layer);
    return scene;
}

bool EggRoomLayer::init() {
    if (!CCLayer::init())
        return false;

    GameManager::get()->fadeInMusic("man.ogg"_spr);

    geode::addBackButton(this);

    this->setMouseEnabled(true);
    this->setTouchEnabled(true);
    this->setKeyboardEnabled(true);
    this->setKeypadEnabled(true);

    CCSprite* floorCircle = CCSprite::create("floorCircle.png"_spr);
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

    EggTree* tree = EggTree::create();
    tree->setPosition(floorCircle->getPosition());
    tree->setID("tree");

    CCMenu* dialogMenu = CCMenu::create();
    dialogMenu->setID("dialog-menu");

    CCMenuItem* dialogButton = CCMenuItemExt::create([this](CCMenuItem* item){
        this->dialogButtonClicked(item);
    });
    dialogButton->setID("dialog-button");
    dialogButton->setPositionY(15.f);
    dialogButton->setContentSize({120.f, 85.f});

    dialogMenu->addChild(dialogButton);

    this->addChild(floorCircle);
    this->addChild(floorSquare);
    this->addChild(tree);
    this->addChild(dialogMenu);

    return true;
}

void EggRoomLayer::dialogButtonClicked(CCMenuItem* sender) {
    FLAlertLayer::create("", "(He is behind the tree.)", "OK")->show();
}

void EggRoomLayer::keyBackClicked() {
    CCDirector::get()->popSceneWithTransition(.5f, PopTransition::kPopTransitionFade);
}

void EggRoomLayer::onExit() {
    CCLayer::onExit();
    GameManager::get()->playMenuMusic();
}