#include "ExamScene.h"
#include "SimpleAudioEngine.h"
#include "Project/game/StaffLayer.h"
#include "Project/game/WaveFormLayer.h"
#include "Project/game/PianoKeyLayer.h"

USING_NS_CC;

bool ExamScene::init()
{
    //////////////////////////////
    if (!Scene::init())
    {
        return false;
    }

    setAnchorPoint(Point::ZERO);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("staff.plist", "staff.pvr.ccz");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


//    WaveFormLayer *_waveFormLyer = WaveFormLayer::create();
//    this->addChild(_waveFormLyer, 0);

    StaffLayer *_staffLayer = StaffLayer::create();
//    _staffLayer->setContentSize(Size());
    //float _staffLayerHeight = visibleSize.height - _waveFormHeight - _pianoKeyHeight;
    //_staffLayer->setContentSize(CCSizeMake(visibleSize.width, _staffLayerHeight));
    //Sprite* sprite = Sprite::create("staff_back.png");
//	_staffLayer->setPosition(Point::ZERO);
//	_staffLayer->setAnchorPoint(Point::ZERO);
    //_staffLayer->addChild(sprite);
    this->addChild(_staffLayer, 1);

    PianoKeyLayer *_pianoKeyLayer = PianoKeyLayer::create();
//	float _pianoKeyHeight = visibleSize.height * 0.076;
//	_pianoKeyLayer->setContentSize(CCSizeMake(visibleSize.width, _pianoKeyHeight));
//	_pianoKeyLayer->setAnchorPoint(Point::ZERO);
//	_pianoKeyLayer->setPosition(origin.x, origin.y + _pianoKeyHeight);
    this->addChild(_pianoKeyLayer, 2);


    MenuItemImage *closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(ExamScene::menuCloseCallback, this));

    closeItem->setPosition(
            Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                 origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    Menu *menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
    return true;
}

void ExamScene::menuCloseCallback(Ref *pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}