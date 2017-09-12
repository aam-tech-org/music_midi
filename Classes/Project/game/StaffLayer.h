#ifndef __STAFF_LAYER_H__
#define __STAFF_LAYER_H__

#include "cocos2d.h"
#include "Project/common/ExamMidiSystem.h"

static const int _STAFF_HEIGHT_ = 1506;

enum MIDI_PLAY_STATE
{
    PLAY_STATE_NORMA = 0,
    PLAY_STATE_PLAYING,
    PLAY_STATE_STOP,
    PLAY_STATE_PAUSE,
};

class StaffLayer : public cocos2d::Layer
{

public:
    StaffLayer();

    ~StaffLayer();

    virtual bool init();

    void playCallback(StaffNote _staffNote);

    void playMove();

    void moveCallback(Node *_node, StaffNote _staffNote);

    void onEnter() override;

    void onExit() override;

    CREATE_FUNC(StaffLayer);
private:
    ExamMidiSystem _m_examMidiSystem;
    EventListenerTouchOneByOne *l;
    int _playIndex = 0;
    int _pageIndex = 0;
    MidiDriver _midiDriver;
    MIDI_PLAY_STATE _playState = PLAY_STATE_NORMA;
};

#endif //__STAFF_LAYER_H__
