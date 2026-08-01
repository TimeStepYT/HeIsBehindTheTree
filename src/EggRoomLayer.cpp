#include "EggRoomLayer.hpp"
#include "EggTree.hpp"

#include <timestepyt.deltarune_textboxes/api/API.hpp>

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

    // I want this to always be the default sound if you have Deltarune Textboxes
    deltarune_textboxes::lockTextSound("Default").unwrapOrDefault();

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

void EggRoomLayer::showAlert(std::string const& text) {
    FLAlertLayer::create("", text, "OK")->show();
}

void EggRoomLayer::showDefaultMessage() {
    this->showAlert("(Well, there is not a man here.)");
}

void EggRoomLayer::receiveEgg() {
    FMODAudioEngine::sharedEngine()->playEffect("snd_egg.wav"_spr);
    Mod::get()->setSavedValue<bool>("received-egg", true);
}

void EggRoomLayer::eggSequence() {
    std::string text1 = "(Well, there is a man here.)";
    std::string text2 = "(He offered you something.)";
    std::string text3 = "(You received an Egg.)";

    FLAlertLayer* alert = geode::createQuickPopup("", text1, "OK", nullptr,
        [this, text2, text3](FLAlertLayer* layer, bool) {
            geode::createQuickPopup("", text2, "Yes", "No", 
                [this, text3](FLAlertLayer* layer2, bool btn2) {
                    if (btn2)
                        this->showDefaultMessage();
                    else {
                        this->showAlert(text3);
                        this->receiveEgg();
                    }
                }
            );
        }
    );
}

void EggRoomLayer::dialogButtonClicked(CCMenuItem* sender) {
    switch (this->m_buttonInteractCounter) {
    case 0:
        this->showAlert("(He is behind the tree.)");
        break;
    case 1:
        this->eggSequence();
        break;
    default:
        this->showDefaultMessage();
        break;
    }
    this->m_buttonInteractCounter++;
}

void EggRoomLayer::keyBackClicked() {
    CCDirector::get()->popSceneWithTransition(.5f, PopTransition::kPopTransitionFade);
}

void EggRoomLayer::onExit() {
    CCLayer::onExit();
    deltarune_textboxes::unlockTextSound();

    GameManager::get()->playMenuMusic();
}