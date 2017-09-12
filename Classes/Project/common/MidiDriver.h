//
// Created by hw on 2017/8/4.
//

#ifndef PROJ_ANDROID_STUDIO_MIDIDRIVER_H
#define PROJ_ANDROID_STUDIO_MIDIDRIVER_H

#include <jni.h>
#include "cocos2d.h"
#include "string"

using namespace std;

USING_NS_CC;

class MidiDriver {
public:
    MidiDriver();

    ~MidiDriver();

    bool init();

    void start();

    void stop();

    void sendMidiMsg(unsigned char _m, unsigned char _n, unsigned char v);

private:
    //类名
    const char *_m_strClassName = "com/made/midi/MadeMidiDriver";
//    JniMethodInfo _m_init;
    JniMethodInfo _m_start;
    JniMethodInfo _m_stop;
    JniMethodInfo _m_sendMidiMsg;
};


#endif //PROJ_ANDROID_STUDIO_MIDIDRIVER_H
