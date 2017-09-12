//
// Created by hw on 2017/7/31.
//

#include <ui/UIEditBox/UIEditBox.h>
#include "LoginScene.h"
#include "ExamScene.h"

USING_NS_CC;

LoginScene::LoginScene() {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("staff.plist", "staff.pvr.ccz");
}

LoginScene::~LoginScene() {

}

bool LoginScene::init() {
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    setAnchorPoint(Point::ZERO);

    Sprite *_m_bgSprite = Sprite::createWithSpriteFrameName("scene_staff_back.png");
    _m_bgSprite->setPosition(Point(origin.x, origin.y));
    _m_bgSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    _m_bgSprite->setAnchorPoint(Point::ZERO);
    addChild(_m_bgSprite);

    Sprite *_m_logoSprite = Sprite::createWithSpriteFrameName("login_logo.png");
    _m_logoSprite->setContentSize(Size(visibleSize.width, 241));
    _m_logoSprite->setAnchorPoint(Point(0, 1));
    _m_logoSprite->setPosition(Point(origin.x, origin.y + visibleSize.height));
    addChild(_m_logoSprite);


    Layer *_m_loginRoot = Layer::create();
    _m_loginRoot->setContentSize(Size(578, 686));
    _m_loginRoot->setAnchorPoint(Point::ZERO);
    _m_loginRoot->setPosition(
            Point((visibleSize.width - _m_loginRoot->getContentSize().width) / 2 + origin.x,
                  (visibleSize.height - _m_loginRoot->getContentSize().height) / 2 + origin.y));
    addChild(_m_loginRoot);

    Label *_m_loginInputTicket = Label::createWithTTF("请输入您的准考证号", "fonts/msyh.ttc", 32);
    _m_loginInputTicket->setString("请输入您的准考证号");
    _m_loginInputTicket->setAnchorPoint(Point::ZERO);
    _m_loginInputTicket->setPosition(Point((_m_loginRoot->getContentSize().width -
                                            _m_loginInputTicket->getContentSize().width) / 2 +
                                           origin.x,
                                           _m_loginRoot->getContentSize().height -
                                           _m_loginInputTicket->getContentSize().height +
                                           origin.y));
    _m_loginInputTicket->setTextColor(Color4B::WHITE);
    _m_loginRoot->addChild(_m_loginInputTicket);

    Label *_m_accountLabel = Label::createWithTTF("账号:", "fonts/msyh.ttc", 32);
    _m_accountLabel->setString("账号:");
    _m_accountLabel->setTextColor(Color4B::WHITE);
    _m_accountLabel->setAnchorPoint(Point::ZERO);
    _m_accountLabel->setPosition(Point(origin.x, origin.y + 544));
    _m_loginRoot->addChild(_m_accountLabel);

    _m_accountEeditText = ui::EditBox::create(Size(578, 84), "login_input_bg.png",
                                              ui::Widget::TextureResType::PLIST);
    _m_accountEeditText->setAnchorPoint(Point::ZERO);
    _m_accountEeditText->setPosition(Point(origin.x, origin.y + 448));
    _m_accountEeditText->setFontColor(Color4B::BLACK);
    _m_accountEeditText->setMaxLength(30);
    _m_accountEeditText->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    _m_loginRoot->addChild(_m_accountEeditText);

    Label *_m_pwdLabel = Label::createWithTTF("密码:", "fonts/msyh.ttc", 32);
    _m_pwdLabel->setString("密码:");
    _m_pwdLabel->setTextColor(Color4B::WHITE);
    _m_pwdLabel->setAnchorPoint(Point::ZERO);
    _m_pwdLabel->setPosition(Point(origin.x, origin.y + 360));
    _m_loginRoot->addChild(_m_pwdLabel);

    _m_pwdEeditText = ui::EditBox::create(Size(578, 84), "login_input_bg.png",
                                          ui::Widget::TextureResType::PLIST);
    _m_pwdEeditText->setAnchorPoint(Point::ZERO);
    _m_pwdEeditText->setPosition(Point(origin.x, origin.y + 260));
    _m_pwdEeditText->setFontColor(Color4B::BLACK);
    _m_pwdEeditText->setMaxLength(30);
    _m_pwdEeditText->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    _m_loginRoot->addChild(_m_pwdEeditText);

    _m_btnLogin = Sprite::createWithSpriteFrameName("btn_login.png");
    _m_btnLogin->setAnchorPoint(Point::ZERO);
    _m_btnLogin->setPosition(Size(origin.x, origin.y));
    _m_btnLogin->setContentSize(Size(578, 96));
    _m_loginRoot->addChild(_m_btnLogin);

    EventListenerTouchOneByOne *_listener = EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(LoginScene::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(LoginScene::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(LoginScene::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
    return true;
}

bool LoginScene::onTouchBegan(Touch *tTouch, Event *eEvent) {
    Point locationInNode = _m_btnLogin->convertToNodeSpace(tTouch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
    if (_m_btnLogin->isVisible() &&
        _m_btnLogin->getBoundingBox().containsPoint(locationInNode)) {//判断触摸点是否在目标的范围内
        return true;
    }
    return false;
}

void LoginScene::onTouchMoved(Touch *tTouch, Event *eEvent) {
}

void LoginScene::onTouchEnded(Touch *tTouch, Event *eEvent) {
    Point locationInNode = _m_btnLogin->convertToNodeSpace(tTouch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
    if (_m_btnLogin->isVisible() &&
        _m_btnLogin->getBoundingBox().containsPoint(locationInNode)) {//判断触摸点是否在目标的范围内
        Director::getInstance()->replaceScene(ExamScene::create());
    }
}