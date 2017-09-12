//
// Created by hw on 2017/8/5.
//

#include "ExamMidiSystem.h"

using namespace cocos2d;

ExamMidiSystem::ExamMidiSystem()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("staff.plist",
                                                             "staff.pvr.ccz");
    _m_iPageLineCount = (STAFF_HEIGHT - STAFF_MARGIN_TOP - STAFF_MARGIN_BOTTOM) / 150;
    bool b = _midiDriver.init();
}

ExamMidiSystem::~ExamMidiSystem()
{
//    if(nullptr != _staffPages){
//        delete _staffPages;
//    }
//    if(nullptr != _midiNodeArray){
//        delete _midiNodeArray;
//    }
}

bool ExamMidiSystem::loadFile(const char *fileName)
{
    if (fileName == NULL)
    {
        return false;
    }
    return _midi.load(fileName);
}

void ExamMidiSystem::process()
{
    _midi.process();
    _trackCount = _midi.getTrackCount();

    int *_metaSpeedDefaut = _midi.getMetaSpeedDefault();
    int *_metaBeatDefault = _midi.getMetaBeatDefault();
    std::vector<int> _beatPercentArray;
    int _noteRhythmCount = 0;
//    int _noteBadrBeat = 4 * 2;

    if (_metaBeatDefault)
    {
        _noteRhythmCount = _metaBeatDefault[0] * 2;
//        _noteBadrBeat = pow(2, _metaBeatDefault[1]) * 2;
    }

    for (int i = 0; i < _trackCount; i++)
    {
        MIDI_TRACK *_track = _midi.getTrack(i);

        if (_midiSys.processTrack(_track))
        {
            MIDI_NODE_ARRAY &_array = _midiSys.getList();

            MidiNoteSystem _mns(_array);
            MidiNoteSystem::NOTE_NODE_ARRAY &_midiNoteArray = _mns.getNoteArray();

            for (int j = 0; j < _midiNoteArray.size(); j++)
            {
                MidiNoteSystem::NOTE_NODE *_pmnn = _midiNoteArray[j];

                for (int n = 0; n < 16; n++)
                {
                    MidiNoteSystem::NOTE *_note = _pmnn->_note[n];

                    if (_note && (*_note->_minBeat) > 0 && _note->getLevel() > 3 &&
                        _note->getLevel() < 7)
                    {
                        _beatPercentArray.push_back(_note->getBeatPercent());
                        StaffNote _staffNote;
                        _staffNote.setNote(*_pmnn->_note[n]);
                        log("****  _pmnn->_note[n]->_bNot i = %i ****", (unsigned int)_pmnn->_note[n]->_bNote);
                        _midiNodeArray.push_back(_staffNote);
                    }
                }
            }
        }
    }

    unsigned int _nodeBeatPercent = 0;
    std::vector<int> _nodeNoteArray;
    std::vector<int> _nodeBeatPercentArray;
    staffLine *_staffLine;
    float x = 0;
    Sprite *_staffPage;
    int _lineNumber = 0;
    const float _staffline_width_flag = 43.0f;
    const float _staffline_height = 150.0f;
    stringstream ss;
    bool isLineFirst = false, isPageFirst = false;
    for (int i = 0; i < _midiNodeArray.size(); i++)
    {
        _nodeNoteArray.push_back(i);
        int _beatPercent = _beatPercentArray.at(i);
        _nodeBeatPercentArray.push_back(_beatPercent);
        _nodeBeatPercent += _beatPercent;
        float width = STAFF_LINE_WIDTH;

        if (i == 0)
        {
            x += 114;
            _staffLine = createLine(width - 64, STAFF_NOTE_LINE_WIDTH, _lineNumber);
            _staffPage = Sprite::createWithSpriteFrameName("staff_back.png");
            _staffPage->setContentSize(Size(1080, STAFF_HEIGHT));
            _staffPage->setAnchorPoint(Point::ZERO);
            _staffPage->setPosition(Point::ZERO);

            int y = STAFF_HEIGHT - STAFF_MARGIN_TOP - _staffline_height;
            _staffLine->setAnchorPoint(Point::ZERO);
            _staffLine->setPosition(Point(164, y));
            _staffPage->addChild(_staffLine);

            Sprite *_playSectionLine = Sprite::createWithSpriteFrameName(
                    "play_section_line.png");
            _playSectionLine->setAnchorPoint(Point::ZERO);
            _playSectionLine->setContentSize(Size(12, 70));
            _playSectionLine->setPosition(Point(100, _staffLine->getPosition().y));
            _playSectionLine->setName(PLAY_SECTION_LINE_NAME);
            _staffPage->addChild(_playSectionLine);

            _staffPages.push_back(_staffPage);
            isLineFirst = true;
        }

        if (_nodeBeatPercent >= _noteRhythmCount || i == _midiNodeArray.size() - 1)
        {
            if (x + (_nodeNoteArray.size() * STAFF_SLUR_LINE_WIDTH) >
                _staffLine->getContentSize().width)
            {
                _lineNumber++;
                _staffLine = createLine(width, STAFF_NOTE_LINE_WIDTH, _lineNumber);
                isLineFirst = true;
                int y = STAFF_HEIGHT - STAFF_MARGIN_TOP - (_lineNumber + 1) * _staffline_height;
                _staffLine->setAnchorPoint(Point::ZERO);
                _staffLine->setPosition(Point(100, y));
                if (_staffPages.size() % 8 == 0)
                {
                    _staffPage = Sprite::createWithSpriteFrameName("staff_back.png");
                    _staffPage->setContentSize(Size(1080, STAFF_HEIGHT));
                    _staffPage->setAnchorPoint(Point::ZERO);
                    _staffPage->setPosition(Point::ZERO);

                    Sprite *_playSectionLine = Sprite::createWithSpriteFrameName(
                            "play_section_line.png");
                    _playSectionLine->setAnchorPoint(Point::ZERO);
                    _playSectionLine->setContentSize(Size(12, 70));
                    _playSectionLine->setPosition(Point(100, _staffLine->getPosition().y));
                    _playSectionLine->setName(PLAY_SECTION_LINE_NAME);
                    _staffPage->addChild(_playSectionLine);

                    _staffPages.push_back(_staffPage);
                }

                _staffPage->addChild(_staffLine);
                x = 98;
            }
            bool isDrawSlurLine = false;
            float _sysmolHeight = STAFF_NOTE_DEFAULT_HEIGHT;
            float _nextSysmolHeight = 0;
            int _heightFlag = 0;
            for (int j = 0; j < _nodeNoteArray.size(); j++)
            {
                StaffNote &_curSaffNote = _midiNodeArray.at(_nodeNoteArray.at(j));
                if (isLineFirst)
                {
                    _curSaffNote.setLineFirst(true);
                    isLineFirst = false;
                } else
                {
                    _curSaffNote.setLineFirst(false);
                }

//                if (_isPageLast)
//                {
//                    _curSaffNote.setIsPageFirst(_isPageLast);
//                    _isPageLast = false;
//                } else
//                {
//                    _curSaffNote.setIsPageFirst(false);
//                }
                _curSaffNote.setLineName(_staffLine->getName());
                _curSaffNote.setPageNumber(_staffPages.size() - 1);
                ss.str("");
                ss << _lineNumber << "_" << x;
                _curSaffNote.setName(ss.str());
                MidiNoteSystem::NOTE _curNote = _curSaffNote.getNote();
                x += STAFF_SLUR_LINE_WIDTH;
                int _beatPercent = _nodeBeatPercentArray.at(j);
                int _level = _curNote.getLevel();
                ENUM_MIDI_VOICE_HEIGHT _emvh = _curNote.getHeight();

//                int _nextBeatPercent = 0;
                bool _isAbove = getSysmolDirection(_level);
                bool _isHalfNote = _beatPercent * 2 == _noteRhythmCount;
                bool isDrawTail = false;
                bool _isDrawSharp = isDrawSharp(_emvh);
                if (_beatPercent == 1)
                {
                    if (j < _nodeNoteArray.size() - 1)
                    {
                        int _nextBeatPercent = _nodeBeatPercentArray.at(j + 1);
                        if (_nextBeatPercent > 1)
                        {
                            isDrawTail = !isDrawSlurLine;
                            isDrawSlurLine = false;
                            if (_heightFlag == 1)
                            {
                                _heightFlag++;
                            }
                        } else
                        {
                            isDrawSlurLine = !isDrawSlurLine;
                            if (isDrawSlurLine && _heightFlag == 0)
                            {
                                _heightFlag++;
                            } else
                            {
                                if (_heightFlag == 1)
                                {
                                    _heightFlag++;
                                }
                            }
                        }
                    } else
                    {
                        isDrawTail = !isDrawSlurLine;
                        isDrawSlurLine = false;
                        if (_heightFlag == 1)
                        {
                            _heightFlag++;
                        }
                    }
                } else if (_beatPercent == 2)
                {
                    isDrawSlurLine = false;
                    _heightFlag = 0;
                } else if (_beatPercent == 3)
                {
                    isDrawSlurLine = false;
                    _heightFlag = 0;
                } else if (_beatPercent == 4)
                {
                    isDrawSlurLine = false;
                    _heightFlag = 0;
                } else
                {
                    isDrawSlurLine = false;
                    _heightFlag = 0;
                }

                if (_heightFlag == 1)
                {
                    if (j < _nodeNoteArray.size() - 1)
                    {
                        StaffNote _nextStaffNote = _midiNodeArray.at(_nodeNoteArray.at(j + 1));
                        MidiNoteSystem::NOTE _nextNote = _nextStaffNote.getNote();
                        float _curIndex = getIndex(_curNote.getLevel(), _curNote.getHeight());
                        float _nextIndex = getIndex(_nextNote.getLevel(),
                                                    _nextNote.getHeight());
                        float _sysmolHeightDiff = 0;
                        if (_nextIndex > _curIndex)
                        {
                            _sysmolHeightDiff =
                                    STAFF_NOTE_LINE_WIDTH *
                                    fabs(_curIndex - _nextIndex);

                            if (_isAbove)
                            {
                                _sysmolHeight = _sysmolHeight + _sysmolHeightDiff;
                                _nextSysmolHeight = STAFF_NOTE_DEFAULT_HEIGHT;
                            } else
                            {
                                _sysmolHeight = -STAFF_NOTE_DEFAULT_HEIGHT;
                                _nextSysmolHeight = -STAFF_NOTE_DEFAULT_HEIGHT - _sysmolHeightDiff;
                            }

                        } else if (_nextIndex == _curIndex)
                        {
                            if (_isAbove)
                            {
                                _sysmolHeight = STAFF_NOTE_DEFAULT_HEIGHT;
                                _nextSysmolHeight = _sysmolHeight;
                            } else
                            {
                                _sysmolHeight = -STAFF_NOTE_DEFAULT_HEIGHT;
                                _nextSysmolHeight = -STAFF_NOTE_DEFAULT_HEIGHT;
                            }
                        } else
                        {
                            _sysmolHeightDiff =
                                    STAFF_NOTE_LINE_WIDTH * fabs(_nextIndex - _curIndex);
                            if (_isAbove)
                            {
                                _sysmolHeight = STAFF_NOTE_DEFAULT_HEIGHT;
                                _nextSysmolHeight = STAFF_NOTE_DEFAULT_HEIGHT + _sysmolHeightDiff;
                            } else
                            {
                                _sysmolHeight = 0 - STAFF_NOTE_DEFAULT_HEIGHT - _sysmolHeightDiff;
                                _nextSysmolHeight = -STAFF_NOTE_DEFAULT_HEIGHT;
                            }
                        }
                    }
                } else if (_heightFlag == 2)
                {
                    _heightFlag = 0;
                    _sysmolHeight = _nextSysmolHeight;
                } else
                {
                    if (_isAbove)
                    {
                        _sysmolHeight = STAFF_NOTE_DEFAULT_HEIGHT;
                    } else
                    {
                        _sysmolHeight = -STAFF_NOTE_DEFAULT_HEIGHT;
                    }
                }
                drawSysmol(_staffLine, _curNote, x, _beatPercent, _isHalfNote,
                           _sysmolHeight, isDrawSlurLine, 1, _isAbove, isDrawTail,
                           _isDrawSharp, ss.str());
//                if(j == ){
//
//                }
            }
            _nodeBeatPercent = 0;
            _nodeNoteArray.clear();
            _nodeBeatPercentArray.clear();
            x += 27;
            Sprite *sectionline = Sprite::createWithSpriteFrameName(
                    "section_line.png");
            sectionline->setScale(0.42f);
            sectionline->setPosition(Point(x, _staffLine->getTrackPositinY(3)));
            _staffLine->addChild(sectionline);
        }
    }
}

void ExamMidiSystem::drawSplitSymbol(staffLine *_staffLine, MidiNoteSystem::NOTE *_note, float x,
                                     int _nextBeatPercent, bool isFalfNote, float _height,
                                     bool isDrawSlurLine, int _count, bool _isAbove,
                                     bool isDrawTail,
                                     bool isDrawSharp)
{
    int _level = _note->getLevel();
    ENUM_MIDI_VOICE_HEIGHT _emvh = _note->getHeight();
    float _index = getIndex(_level, _emvh);
    staffSymbol *_staffSymbol = createStaffSymbol(_staffLine, _index, x, isFalfNote,
                                                  _height);
    if (isDrawSlurLine)
    {
        drawSlurLine(_staffSymbol, _count, _isAbove);
    }
    if (isDrawTail)
    {
        drawTail(_staffSymbol, _isAbove);
    }
    if (isDrawSharp)
    {
        drawSharp(_staffSymbol);
    }
    _staffLine->addChild(_staffSymbol);
}

void ExamMidiSystem::drawSysmol(staffLine *_staffLine, MidiNoteSystem::NOTE _note, float x,
                                int _nextBeatPercent, bool isFalfNote, float _height,
                                bool isDrawSlurLine, int _count, bool _isAbove, bool isDrawTail,
                                bool isDrawSharp, string _tagName)
{
    int _level = _note.getLevel();
    ENUM_MIDI_VOICE_HEIGHT _emvh = _note.getHeight();
    float _index = getIndex(_level, _emvh);
    staffSymbol *_staffSymbol = nullptr;
    if (_nextBeatPercent == 8)
    {
        _staffSymbol = createStaffSymbol(_staffLine, _index, x, !isFalfNote, 1);
    } else
    {
        _staffSymbol = createStaffSymbol(_staffLine, _index, x, isFalfNote, _height);
    }
    _staffSymbol->setName(_tagName);
    if (isDrawSlurLine)
    {
        drawSlurLine(_staffSymbol, _count, _isAbove);
    }
    if (isDrawTail)
    {
        drawTail(_staffSymbol, _isAbove);
    }
    if (isDrawSharp)
    {
        drawSharp(_staffSymbol);
    }
    if (_index <= 0)
    {
        int count = fabs(_index) / 1;
        for (int i = 0; i <= count; i++)
        {
            drawNextLine(_staffSymbol, _index, i);
        }
    }
    _staffLine->addChild(_staffSymbol);
}

void ExamMidiSystem::drawSlurLine(staffSymbol *_staffSymbol, int _count, bool _isAbove)
{
    staffSymbolLine *_staffSymbolLine = staffSymbolLine::create();
    _staffSymbolLine->setAnchorPoint(Point::ZERO);
    _staffSymbolLine->initSBLine(STAFF_SLUR_LINE_WIDTH, _count);
    if (_isAbove)
    {
        _staffSymbolLine->setPosition(
                Point(_staffSymbol->getContentSize().width - 1,
                      _staffSymbol->getContentSize().height - STAFF_NOTE_LINE_HEIGHT));
    } else
    {
        _staffSymbolLine->setPosition(Point(0, STAFF_NOTE_LINE_WIDTH * 1.5));
    }
    _staffSymbol->addChild(_staffSymbolLine);
}

void ExamMidiSystem::drawTail(staffSymbol *_staffSymbol, bool _isAbove)
{
    Sprite *_sprite = Sprite::createWithSpriteFrameName("note_tail.png");
    _sprite->setScale(0.25);
    _sprite->setAnchorPoint(Point::ZERO);
    if (_isAbove)
    {
        _sprite->setPosition(Point(_staffSymbol->getContentSize().width - 1,
                                   _staffSymbol->getContentSize().height -
                                   _sprite->getContentSize().height * 0.25 -
                                   STAFF_NOTE_LINE_WIDTH));
    } else
    {
        _sprite->setFlippedY(true);
        _sprite->setPosition(Point(0, STAFF_NOTE_LINE_WIDTH));
    }
    _staffSymbol->addChild(_sprite);
}

void ExamMidiSystem::drawNextLine(staffSymbol *_staffSymbol, float _index, int position)
{
    DrawNode *_drawNote = DrawNode::create();
    _drawNote->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    float y = 4;
    if ((int) (fabs(_index) * 10) % 2 == 1)
    {
        y += 4 + position * 10;
    } else
    {
        y += position * 10;
    }
    _drawNote->setPosition(
            Point(_staffSymbol->getContentSize().width * 0.5, y));
    Point _from(-10, 0);
    Point _to(10, 0);
    _drawNote->drawLine(_from, _to, Color4F::BLACK);
    _staffSymbol->addChild(_drawNote);
}

void ExamMidiSystem::drawSharp(staffSymbol *_staffSymbol)
{
    Sprite *_sprite = Sprite::createWithSpriteFrameName("note_sharp.png");
    _sprite->setScale(0.3);
    _sprite->setAnchorPoint(Point::ZERO);
    _sprite->setPosition(-_sprite->getContentSize().width * 0.3,
                         -_sprite->getContentSize().height * 0.3 * 0.5 +
                         STAFF_NOTE_LINE_HEIGHT * 1.5);
    _staffSymbol->addChild(_sprite);
}

staffLine *ExamMidiSystem::createLine(float _width, float _height, int _lineNumber)
{
    staffLine *_staffLine = staffLine::create();
    _staffLine->initLine(_width, _height);
    Sprite *clef = Sprite::createWithSpriteFrameName("clef_g.png");
    clef->setPosition(22, _staffLine->getTrackPositinY(3));
    clef->setScale(0.3);
    _staffLine->addChild(clef);

    stringstream ss;
    ss << "_" << _lineNumber;
    _staffLine->setName(ss.str());
    return _staffLine;
}

staffSymbol *
ExamMidiSystem::createStaffSymbol(staffLine *_staffLine, float _index,
                                  float x, bool isFalfNote, float _lineHeight)
{
    staffSymbol *_staffSymbol = staffSymbol::create();
    _staffSymbol->initSymbol(STAFF_NOTE_LINE_WIDTH, STAFF_NOTE_LINE_HEIGHT, !isFalfNote,
                             _lineHeight);
    _staffSymbol->setPosition(x, _staffLine->getTrackPositinY(_index));
    return _staffSymbol;
}

Node *ExamMidiSystem::getStaffPage(int index)
{
    if (_staffPages.empty() || index > _staffPages.size() - 1)
    {
        return nullptr;
    }
    return _staffPages.at(index);
}

float ExamMidiSystem::getIndex(const int _level, const ENUM_MIDI_VOICE_HEIGHT _emvh)
{
    float _index;

    if (_level == 4)
    {
        _index = -3.5;
    } else if (_level == 5)
    {
        _index = 0;
    } else if (_level == 6)
    {
        _index = 3.5;
    }
    int _e = EMVH_C;
    for (; _e <= EMVN_B; _e++)
    {
        if (_e == _emvh)
        {
            break;
        }
        if (_e != EMVH_Cx && _e != EMVH_Dx && _e != EMVH_Fx && _e != EMVH_Gx && _e != EMVH_Ax)
        {
            _index += 0.5;
        }
    }
    if (_emvh == EMVH_Cx || _emvh == EMVH_Dx || _emvh == EMVH_Fx || _emvh == EMVH_Gx ||
        _emvh == EMVH_Ax)
    {
        _index -= 0.5;
    }
    return _index;
}

float ExamMidiSystem::getSymbolHeight(bool _isDrawSlurLine, bool _isAbove, float _curIndex,
                                      float _nextIndex)
{
    float _height;
    if (_isDrawSlurLine)
    {

        if (_nextIndex > _curIndex)
        {
            _height =
                    STAFF_NOTE_DEFAULT_HEIGHT -
                    STAFF_NOTE_LINE_WIDTH * fabs(_curIndex - _nextIndex);
        } else
        {
            _height = STAFF_NOTE_DEFAULT_HEIGHT +
                      STAFF_NOTE_LINE_WIDTH * fabs(_curIndex - _nextIndex);
        }
        if (!_isAbove)
        {
            _height = -_height;
        }
    } else if (_isAbove)
    {
        _height = STAFF_NOTE_DEFAULT_HEIGHT;
    } else
    {
        _height = -STAFF_NOTE_DEFAULT_HEIGHT;
    }
    return _height;
}

bool ExamMidiSystem::getSysmolDirection(int _level)
{

    return _level < 6;
}

bool ExamMidiSystem::isDrawSharp(ENUM_MIDI_VOICE_HEIGHT _emvh)
{
    return ENUM_MIDI_VOICE_HEIGHT::EMVH_Ax == _emvh
           || ENUM_MIDI_VOICE_HEIGHT::EMVH_Cx == _emvh
           || ENUM_MIDI_VOICE_HEIGHT::EMVH_Dx == _emvh
           || ENUM_MIDI_VOICE_HEIGHT::EMVH_Fx == _emvh
           || ENUM_MIDI_VOICE_HEIGHT::EMVH_Gx == _emvh;
}

STAFF_NOTE_ARRAY ExamMidiSystem::getMidiNodeArray()
{
    return _midiNodeArray;
}

void ExamMidiSystem::play()
{
//    std::thread t(&ExamMidiSystem::playMidi, this);
//    t.detach();

    playMidi();
}

void ExamMidiSystem::playMidi()
{


//    JavaVM *vm;
//    JNIEnv *env;
//    vm = JniHelper::getJavaVM();
//
//    JavaVMAttachArgs thread_args;
//
//    thread_args.name = "Resource Load";
//    thread_args.version = JNI_VERSION_1_4;
//    thread_args.group = NULL;
//    vm->AttachCurrentThread(&env, &thread_args);

    /*
    _midiDriver.start();
    for (int i = 0; i < _midiNodeArray.size(); i++)
    {
        StaffNote &_staffNote = _midiNodeArray.at(i);
        if (_playCallback)
        {
            _playCallback(_staffNote);
        }
        MidiNoteSystem::NOTE _note = _staffNote.getNote();
        const unsigned char _noteValue = _note._bNote;
        const unsigned char _bVel = _note._bVel;
        _midiDriver.sendMidiMsg(0x90, _noteValue, _bVel);
        usleep(_note._beat / 120 * 80 * 1000);
        _midiDriver.sendMidiMsg(0x80, _noteValue, 0);
    }

    _midiDriver.stop();
     */
//    vm->DetachCurrentThread();
}

void ExamMidiSystem::setPlayCallback(PLAY_CALL_BACK play_call_back)
{
    this->_playCallback = play_call_back;
}