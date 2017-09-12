#include "StaffLayer.h"
#include "Project/common/MadeFileUtils.h"


USING_NS_CC;

StaffLayer::StaffLayer()
{
    _midiDriver.init();
};

StaffLayer::~StaffLayer()
{
};

bool StaffLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    setContentSize(Size(visibleSize.width, 1506));
    setPosition(Point::ZERO);
    setAnchorPoint(Point::ZERO);

    MadeFileUtils madeFileUtils;
    std::string path = madeFileUtils.copyFile("test5.mid");
    if (!_m_examMidiSystem.loadFile(path.data()))
    {
        return false;
    }
    _m_examMidiSystem.process();
    Node *_page = _m_examMidiSystem.getStaffPage(_pageIndex);

    addChild(_page);

    _m_examMidiSystem.setPlayCallback(
            std::bind(&StaffLayer::playCallback, this, std::placeholders::_1));

    l = EventListenerTouchOneByOne::create();
    l->setSwallowTouches(true);

    l->onTouchBegan = [this](Touch *touch, Event *event) -> bool
    {
        if (_playState == PLAY_STATE_PLAYING)
        {
            _playState = PLAY_STATE_PAUSE;
        } else
        {
            _playState = PLAY_STATE_PLAYING;
            playMove();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(l, this);
    return true;
}

void StaffLayer::playMove()
{
    StaffNote _staffNote = _m_examMidiSystem.getMidiNodeArray().at(_playIndex);
    MidiNoteSystem::NOTE _note = _staffNote.getNote();
    const unsigned char _noteValue = _note._bNote;
    const unsigned char _bVel = _note._bVel;
    float _moveToX = 100;
    if (!_staffNote.getLineName().empty() && _staffNote.getLineName().substr(1) == "0")
    {
        _moveToX += 43;
    }
    if (&_staffNote)
    {
        Node *_page = _m_examMidiSystem.getStaffPage(_staffNote.getPageNumber());
        if (!_page)
        {
            return;
        }
        Node *_line = _page->getChildByName(_staffNote.getLineName());
        if (!_line)
        {
            return;
        }
        Node *_staffSymbol = _line->getChildByName(_staffNote.getName());
        if (!_staffSymbol)
        {
            return;
        }
        Node *_playSectionLine = _page->getChildByName(PLAY_SECTION_LINE_NAME);
        if (_playSectionLine)
        {
            if (!_playSectionLine->isVisible())
            {
                _playSectionLine->setVisible(true);
            }
            MoveTo *_moveTo;
            if (_playIndex == _m_examMidiSystem.getMidiNodeArray().size() - 1)
            {
                _moveTo = MoveTo::create(_staffNote.getNote()._last * 0.002,
                                         Point(_staffSymbol->getPosition().x + _moveToX -
                                               _staffSymbol->getContentSize().width,
                                               _line->getPosition().y));
            } else
            {
                _moveTo = MoveTo::create(_staffNote.getNote()._last * 0.002,
                                         Point(_staffSymbol->getPosition().x + _moveToX -
                                               _playSectionLine->getContentSize().width +
                                               STAFF_SLUR_LINE_WIDTH,
                                               _line->getPosition().y));
            }

            Sequence *_sequence = Sequence::create(_moveTo, CallFuncN::create(
                    CC_CALLBACK_1(StaffLayer::moveCallback, this, _staffNote)), NULL);

            if (_staffNote.isLineFirst())
            {
                _playSectionLine->setPosition(100, _line->getPosition().y);
            }
            _playSectionLine->runAction(_sequence);
            _midiDriver.sendMidiMsg(0x90, _noteValue, _bVel);
            _playIndex++;
        }
    }
}

void StaffLayer::moveCallback(Node *_node, StaffNote _staffNote)
{
    _midiDriver.sendMidiMsg(0x80, _staffNote.getNote()._bNote, 0);
    switch (_playState)
    {
        case PLAY_STATE_NORMA:
        {
            break;
        }
        case PLAY_STATE_PLAYING:
        {
            if (_playIndex < _m_examMidiSystem.getMidiNodeArray().size())
            {
                playMove();
            } else
            {
                _playIndex = 0;
                _playState = PLAY_STATE_NORMA;
            }
            break;
        }
        case PLAY_STATE_PAUSE:
        {
            if (!(_playIndex < _m_examMidiSystem.getMidiNodeArray().size()))
            {
                _playIndex = 0;
                _playState = PLAY_STATE_NORMA;
            }
            break;
        }
        case PLAY_STATE_STOP:
        {
            _playIndex = 0;
            break;
        }
    }
}

void StaffLayer::onEnter()
{
    Layer::onEnter();
    _midiDriver.start();
}

void StaffLayer::onExit()
{
    Layer::onExit();
    _midiDriver.stop();
    _playState == PLAY_STATE_PAUSE;
}

void StaffLayer::playCallback(StaffNote _staffNote)
{

}