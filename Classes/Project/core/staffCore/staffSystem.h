//
//  staffSystem.h
//  music_midi
//
//  Created by  fengrh on 2017/8/1.
//
//

#ifndef staffSystem_hpp
#define staffSystem_hpp

#include <stdio.h>
#include "cocos2d.h"

#define MAX_NODE_SIZE 10
#define MAX_STAFF_LINE_SIZE 15

#define STAFF_HEIGHT 1506
#define STAFF_MARGIN_TOP 202
#define STAFF_MARGIN_LEFT 100
#define STAFF_MARGIN_RIGHT 100
#define STAFF_MARGIN_BOTTOM 200
#define STAFF_FIRST_MARGIN_LEFT 143


class staffLine;

class MidiInterface;

class StaffSystem {
public:
    StaffSystem();

    ~StaffSystem() {}

    bool init();

    bool release();

    int loadMidiFile(const char *fileName);

    int getStaffPages();

    cocos2d::Node *getStaffByPage(int pageIndex);

protected:
    MidiInterface *m_midi;
private:
    cocos2d::Node *m_staffNode[MAX_NODE_SIZE];
    staffLine *m_staff5Line[MAX_NODE_SIZE][MAX_STAFF_LINE_SIZE];

    int m_nodePages;
    int m_nodeHeight;
    int m_nodeWidth;
    int m_sectionHeight;
    int m_sectionWidth;
    int m_staffLineHeight;
    int m_staffLineWidth;
    int m_pitchWidth;
    int m_pitchHeight;
    int m_staffHeaderWidth;

    int m_tick;
    int m_metronome;

    int pageLineCount;
};

#endif /* staffSystem_h */
