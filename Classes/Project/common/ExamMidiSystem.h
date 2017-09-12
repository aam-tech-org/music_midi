//
// Created by hw on 2017/8/5.
//

#ifndef PROJ_ANDROID_STUDIO_EXAMMIDISYSTEM_H
#define PROJ_ANDROID_STUDIO_EXAMMIDISYSTEM_H

#define STAFF_HEIGHT 1506
#define STAFF_MARGIN_TOP 202
#define STAFF_MARGIN_LEFT 100
#define STAFF_MARGIN_RIGHT 100
#define STAFF_MARGIN_BOTTOM 200
#define STAFF_FIRST_MARGIN_LEFT 143
#define STAFF_LINE_HEIGHT 170
#define MAX_SECTIONS 2
#define STAFF_LINE_WIDTH 880
#define STAFF_NOTE_LINE_WIDTH 10
#define STAFF_NOTE_LINE_HEIGHT 8
#define STAFF_NOTE_DEFAULT_HEIGHT 42
#define STAFF_SLUR_LINE_WIDTH 29
#define PLAY_SECTION_LINE_NAME "play_section_line"


#include <sstream>
#include <functional>
#include "ExamMidiSystem.h"
#include "Project/core/midiCore/memPool.h"
#include "Project/core/midiCore/midiCore.h"
#include "Project/core/staffCore/StaffSystem.h"
#include "Project/core/staffCore/staffLine.h"
#include "Project/core/staffCore/staffSymbol.h"
#include "Project/model/StaffNote.h"
#include "Project/common/MidiDriver.h"

USING_NS_CC;

typedef std::vector<Node *> STAFF_PAGE_ARRAY;
//typedef std::vector<staffLine *> STAFF_LINE_ARRAY;
typedef std::vector<StaffNote> STAFF_NOTE_ARRAY;

typedef std::function<void(StaffNote)> PLAY_CALL_BACK;

class staffLine;

class ExamMidiSystem
{
public:
    ExamMidiSystem();

    ~ExamMidiSystem();
    //加载文件
    bool loadFile(const char *fileName);

    //处理数据
    void process();

    //释放资源
    void release();

    STAFF_NOTE_ARRAY getMidiNodeArray();

    int getStaffPageCount();

    cocos2d::Node *getStaffPage(int index);

//    void getNote();

    void play();

    void start();

    void pause();

    void stop();

    float getIndex(const int _level, const ENUM_MIDI_VOICE_HEIGHT _emvh);

    staffLine *createLine(float _width, float _height, int _lineNumber);

    staffSymbol *
    createStaffSymbol(staffLine *_staffLine, float _index, float x, bool isFalfNote,
                      float _lineHeight);

//    void drawNode(float _positionX,bool isFirst,
//                  STAFF_NOTE_ARRAY _staffNoteArray, std::vector<int> _nodeBeatPercentArray,
//                  int _noteRhythmCount);

    void drawSplitSymbol(staffLine *_staffLine, MidiNoteSystem::NOTE *_note, float x,
                         int _beatPercent, bool isFalfNote, float _height,
                         bool isDrawSlurLine, int _count, bool _isAbove, bool isDrawTail,
                         bool isDrawSharp);

    void drawSysmol(staffLine *_staffLine, MidiNoteSystem::NOTE _note, float x,
                    int _beatPercent, bool isFalfNote, float _height,
                    bool isDrawSlurLine, int _count, bool _isAbove, bool isDrawTail,
                    bool isDrawSharp, string _tagName);

    void drawSlurLine(staffSymbol *_staffSysmol, int _count, bool _isAbove);

    //画下加一线
    void drawNextLine(staffSymbol *_staffSysmol, float _index, int position);

    //画升记号
    void drawSharp(staffSymbol *_staffSysmol);

    //画尾巴
    void drawTail(staffSymbol *_staffSysmol, bool _isAbove);

    float getSymbolHeight(bool _isDrawSlurLine, bool _isAbove, float _curIndex, float _nextIndex);

    bool getSysmolDirection(int _level);

    bool isDrawSharp(ENUM_MIDI_VOICE_HEIGHT _emvh);

    void setPlayCallback(PLAY_CALL_BACK);

private:
    midiCore _midi;
    MidiSystem _midiSys;
//    staffSymbol _staffSymbol;
//    MidiNoteSystem *_midiNoteSysArray[];
    STAFF_NOTE_ARRAY _midiNodeArray;
    int _trackCount;
    STAFF_PAGE_ARRAY _staffPages;
    int _m_iStaffNodeCount;
    int _m_iPageLineCount;
    MidiDriver _midiDriver;
    PLAY_CALL_BACK _playCallback;
    int _startIndex = 0;
    void playMidi();

//    StaffSystem _staffSystem;

};


#endif //PROJ_ANDROID_STUDIO_EXAMMIDISYSTEM_H