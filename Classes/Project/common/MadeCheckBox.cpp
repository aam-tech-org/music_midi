#include "MadeCheckBox.h"

USING_NS_CC;

MadeCheckBox *MadeCheckBox::create(const std::string &checked, const std::string &unchecked) {
    MadeCheckBox *_madeCheckBox = new MadeCheckBox(checked, unchecked);
    if (_madeCheckBox) {
        _madeCheckBox->autorelease();
        return _madeCheckBox;
    }
    CC_SAFE_DELETE(_madeCheckBox);
    return nullptr;
}

MadeCheckBox::MadeCheckBox(const std::string &checkedName, const std::string &uncheckedName) {
    setCheckedBackground(checkedName, uncheckedName);
}

MadeCheckBox::~MadeCheckBox() {
}

bool MadeCheckBox::init() {
    if (!Sprite::init()) {
        return false;
    }


    return true;
}

void MadeCheckBox::setCheckedBackground(const string &checkedName, const string &uncheckedName) {
    this->checkedName = checkedName;
    this->uncheckedName = uncheckedName;
    setChecked(true);

}

void MadeCheckBox::setChecked(bool isChecked) {
    this->isChecked = isChecked;
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(checkedName);
    setSpriteFrame(frame);
}

bool MadeCheckBox::getCheckedState() {
    return isChecked;
}

bool MadeCheckBox::onTouchBegan(Touch *tTouch, Event *eEvent) {

    return true;
}

void MadeCheckBox::onTouchMoved(Touch *tTouch, Event *eEvent) {
}

void MadeCheckBox::onTouchEnded(Touch *tTouch, Event *eEvent) {
    isChecked = !isChecked;
    listener(isChecked);
    setChecked(isChecked);
}

void MadeCheckBox::setOnClickListener(FUN_CLICK_LISTENER l) {
    listener = l;
    EventListenerTouchOneByOne *_listener = EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(MadeCheckBox::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(MadeCheckBox::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(MadeCheckBox::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}