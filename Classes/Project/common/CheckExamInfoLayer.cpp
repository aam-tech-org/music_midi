//
// Created by hw on 2017/8/1.
//

#include "CheckExamInfoLayer.h"
#include "cocos2d.h"

USING_NS_CC;

CheckExamInfoLayer::CheckExamInfoLayer() {
}

CheckExamInfoLayer::CheckExamInfoLayer(char *title, Layer *layer,
                                       const string *button) {

//    if (title->empty()) {
//        throw "title is null";
//    }

    if (!layer) {
        throw "display content is null";
    }

    if (button->empty()) {
        throw "button is null";
    }

    _m_title = Label::createWithTTF(title, "fonts/msyh.tcc", 32);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("staff.plist", "staff.pvr.ccz");
}

CheckExamInfoLayer::~CheckExamInfoLayer() {

}

bool CheckExamInfoLayer::init() {
    if (!Layer::init()) {
        return false;
    }


    EventListenerTouchOneByOne *_listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(true);
    _listener->onTouchBegan = CC_CALLBACK_2(CheckExamInfoLayer::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(CheckExamInfoLayer::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(CheckExamInfoLayer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    return true;
}

bool CheckExamInfoLayer::onTouchBegan(Touch *touch, Event *event) {
    return true;
}

void CheckExamInfoLayer::onTouchMoved(Touch *touch, Event *event) {

}

void CheckExamInfoLayer::onTouchEnded(Touch *touch, Event *event) {


}