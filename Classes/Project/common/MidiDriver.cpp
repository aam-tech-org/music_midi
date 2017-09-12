//
// Created by hw on 2017/8/4.
//

#include "MidiDriver.h"


MidiDriver::MidiDriver() {

}

MidiDriver::~MidiDriver() {

}

bool MidiDriver::init() {
    if (JniHelper::getStaticMethodInfo(_m_start, _m_strClassName, "start", "()V")
        && JniHelper::getStaticMethodInfo(_m_stop, _m_strClassName, "stop", "()V")
        && JniHelper::getStaticMethodInfo(_m_sendMidiMsg, _m_strClassName, "sendMidiMsg", "(BBB)V")
            ) {
        return true;
    }
    return false;
}

void MidiDriver::start() {
    _m_start.env->CallStaticVoidMethod(_m_start.classID, _m_start.methodID);
}

void MidiDriver::stop() {
    _m_stop.env->CallStaticVoidMethod(_m_stop.classID, _m_stop.methodID);
}

void MidiDriver::sendMidiMsg(unsigned char _m, unsigned char _n, unsigned char _v) {
    _m_sendMidiMsg.env->CallStaticVoidMethod(_m_sendMidiMsg.classID, _m_sendMidiMsg.methodID,
                                             _m, _n, _v);
}