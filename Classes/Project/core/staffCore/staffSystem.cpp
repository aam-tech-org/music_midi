//
//  staffSystem.cpp
//  music_midi
//
//  Created by  fengrh on 2017/8/1.
//
//

#include "staffSystem.h"
#include "MidiInterface.h"
#include "staffLine.h"

using namespace cocos2d;

#define MAX_SECTIONS 3

StaffSystem::StaffSystem() {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("staff_note.plist",
                                                             "staff_note.pvr.ccz");
}

bool StaffSystem::init() {
    m_midi = new MidiInterface;
    if (m_midi == NULL) {
        return false;
    }
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_midi->init();

    Sprite *bgsprite = Sprite::createWithSpriteFrameName("staff_back.png");

    Size _bgSize = bgsprite->getContentSize();
    m_nodeWidth = _bgSize.width;
    m_nodeHeight = _bgSize.height;

    m_staffLineWidth = m_nodeWidth * 0.9;
    m_staffLineHeight = m_nodeHeight / (MAX_STAFF_LINE_SIZE * 2);

    m_sectionWidth = m_staffLineWidth * 0.8 / MAX_SECTIONS;
    m_staffHeaderWidth = m_staffLineWidth * 0.05;

    for (int i = 0; i < MAX_NODE_SIZE; i++) {
        m_staffNode[i] = cocos2d::Node::create();

        Sprite *bgsprite = Sprite::createWithSpriteFrameName("staff_back.png");
        bgsprite->setContentSize(Size(visibleSize.width, STAFF_HEIGHT));
        Size _bgSize = bgsprite->getContentSize();
        m_nodeWidth = _bgSize.width;
        m_nodeHeight = _bgSize.height;

        m_staffLineWidth = m_nodeWidth * 0.9;
        m_staffLineHeight = m_nodeHeight / (MAX_STAFF_LINE_SIZE * 2);

        m_sectionWidth = m_staffLineWidth * 0.99 / MAX_SECTIONS;
        m_staffHeaderWidth = m_staffLineWidth * 0.03;
        bgsprite->setAnchorPoint(Point::ZERO);
        //bgsprite->setPosition(Vec2(_bgSize.width / 2 , _bgSize.height /2 ));

        m_staffNode[i]->addChild(bgsprite);

        pageLineCount = (STAFF_HEIGHT - STAFF_MARGIN_TOP - STAFF_MARGIN_BOTTOM) / 170;

        int staffLineWidth = visibleSize.width - 100 * 2;
        for (int j = 0; j < pageLineCount; j++) {
            if (_bgSize.height - 170 * (j + 1) * 2 < 170 * 2) {
                break;
            }
            staffLine *staffline = staffLine::create();
            staffline->setAnchorPoint(Point::ZERO);
            float x, y;
            if (j == 0) {
                staffLineWidth -= 43;
                x = 100 + 43;

            } else {
                x = 100;
            }
            y = pageLineCount - 202 - (j + 1) * 170;
            staffline->setPosition(Point(x, y));
            m_staff5Line[i][j] = staffline;
            staffline->initLine(staffLineWidth, 12);
            bgsprite->addChild(staffline);

//            //draw clef
//            Sprite *clef = Sprite::createWithSpriteFrameName("clef_g.png");
//            clef->setPosition(0, 0);
//            clef->setAnchorPoint(Point(0, 0));
//
//            Size sizeAClef = clef->getContentSize();
//            Size sizeLine = staffline->getContentSize();
//            float scaleX = (float) m_staffHeaderWidth / (float) sizeAClef.width;
//            float scaleY = (float) sizeLine.height / (float) sizeAClef.height;
//            clef->setScale(scaleX, scaleY);
//            staffline->addChild(clef);
//
//            for (int k = 0; k < MAX_SECTIONS; k++) {
//                Sprite *sectionline = Sprite::createWithSpriteFrameName("sectionline.png");
//                sectionline->setPosition(
//                        Vec2(m_staffHeaderWidth + m_sectionWidth * (k + 1), 90 / 2));
//                sectionline->setAnchorPoint(Point(0.5, 0.5));
//
//                Size sizeSectionLine = sectionline->getContentSize();
//                float scaleY = (float) sizeLine.height * 0.67 / (float) sizeSectionLine.height;
//                sectionline->setScaleY(scaleY);
//                staffline->addChild(sectionline);
//            }
        }
    }
    return true;
}

bool StaffSystem::release() {
    if (m_midi != NULL) {
        m_midi->release();
        delete m_midi;
    }
    return 0;
}

int StaffSystem::loadMidiFile(const char *filename) {

    m_midi->loadMidi(filename);

    int _nodeIndex = 0;

    int _stafflineIndex = 0;

    int _pos = 0;

    int _tickcount = 0;
    int _tickindex = 0;

    STAFF_NOTE_ARRAY &_noteArray = m_midi->getNoteList();
    m_metronome = 8;
    int _metronomeWith = m_sectionWidth / m_metronome;

//    for (int i = 0; i < _noteArray.size(); i++) {
//        STAFF_NOTE *_note = _noteArray[i];
//
//        float _height = m_midi->getNoteIndex(_note->_bNote, 3);
//
//        _tickindex = _note->_beginPos / 120 + 1 - _stafflineIndex * 24;
//
//        if (_tickindex > 24) {
//            _stafflineIndex++;
//            _tickindex = 0;
//        }
//
//        if (_stafflineIndex > MAX_STAFF_LINE_SIZE - 2) {
//            _nodeIndex++;
//            _stafflineIndex = 0;
//            _tickindex = 0;
//        }
//
//        if (_nodeIndex > MAX_NODE_SIZE - 2) {
//            break;
//        }
//
//        Sprite *symbol = Sprite::createWithSpriteFrameName("staff_note_4.png");
//
//        symbol->setPosition(
//                Vec2(m_staffHeaderWidth + _tickindex * _metronomeWith - _metronomeWith / 2,
//                     (_height + 2) * 7.5));
//
//        symbol->setScale(0.5, 0.5);
//        if (_height < 6) {
//        } else {
//            symbol->setRotation(180);
//            symbol->setAnchorPoint(Point(0.5, 0));
//        }
//        m_staff5Line[_nodeIndex][_stafflineIndex]->addChild(symbol);
//        _tickcount = _note->_beginPos / 120;
//    }
    return 0;
}

cocos2d::Node *StaffSystem::getStaffByPage(int pageIndex) {
    if (pageIndex > MAX_NODE_SIZE) {
        return NULL;
    }
    return m_staffNode[pageIndex];
}