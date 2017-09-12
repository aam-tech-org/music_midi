#include "PianoKeyLayer.h"
#include <iostream>

USING_NS_CC;
using namespace ui;

PianoKeyLayer::PianoKeyLayer() {
    _m_visibleSize = Director::getInstance()->getVisibleSize();

    _m_fPianoKeyHeight = _m_visibleSize.height * 0.076;
}

PianoKeyLayer::~PianoKeyLayer() {
}

bool PianoKeyLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    _m_pianoSprite = Sprite::createWithSpriteFrameName("staff_piano_key.png");
    _m_pianoSprite->setAnchorPoint(Point::ZERO);
    _m_pianoSprite->setContentSize(Size(_m_visibleSize.width, _m_fPianoKeyHeight));
    addChild(_m_pianoSprite);

    _m_checkbox = CheckBox::create("piano_off.png",
                                   "piano_on.png",
                                   "piano_on.png",
                                   "piano_on.png",
                                   "piano_on.png",
                                   CheckBox::TextureResType::PLIST);
    _m_checkbox->setAnchorPoint(Point::ZERO);
    _m_checkbox->setSelected(true);
    _m_checkbox->setPosition(Point(_m_visibleSize.width - _m_checkbox->getContentSize().width - 10,
                                   _m_fPianoKeyHeight + 10));
    _m_checkbox->addEventListener(CC_CALLBACK_2(PianoKeyLayer::onClick, this));
    this->addChild(_m_checkbox, 1);
    return true;
}

void PianoKeyLayer::onClick(Ref *pSender, CheckBox::EventType type) {
    switch (type) {
        case CheckBox::EventType::SELECTED:
            if (_m_pianoSprite) {
                _m_pianoSprite->setVisible(true);
            }
            _m_checkbox->setPosition(
                    Point(_m_visibleSize.width - _m_checkbox->getContentSize().width - 10,
                          _m_fPianoKeyHeight + 10));
            break;
        case CheckBox::EventType::UNSELECTED:
            _m_pianoSprite->setVisible(false);
            if (_m_checkbox) {
                _m_checkbox->setPosition(
                        Point(_m_visibleSize.width - _m_checkbox->getContentSize().width - 10, 10));
            }
            break;
    }
}