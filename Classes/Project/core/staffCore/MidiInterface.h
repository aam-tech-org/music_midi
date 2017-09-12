//
//  MidiInterface.hpp
//  music_midi
//
//  Created by  fengrh on 2017/7/26.
//
//

#ifndef MidiInterface_hpp
#define MidiInterface_hpp

#include "Project/core/midiCore/midiCore.h"
#include "Project/core/midiCore/memPool.h"

enum {
    STAFF_ACLEF_G  = 0,
    STAFF_ACLEF_F,
    STAFF_ACLEF_C,
};

enum {
    STAFF_4_4 = 0,
    
};

struct STAFF_NOTE
{
    int _beginPos;
    int _endPos;
    char _szNote[16];
    unsigned char _bNote;
    unsigned char _bVel;
    int _flag;
    
};
typedef std::vector<STAFF_NOTE*> STAFF_NOTE_ARRAY;



class MidiInterface {
    
public:
    MidiInterface();
    ~MidiInterface(){}
    
    bool init();
    
    bool release();

    int loadMidi(const char* filename);
  
    STAFF_NOTE_ARRAY& getNoteList();

    MidiSystem* getMidiData(int track);
    
    int getTrackCount();
    
    int getTick();
    
    int getAClef();
    
    int getSpeed();
        
    void CleanNote();
    int m_scale;
    
    int getNoteIndex(MIDI_BYTE bNote, int scale);

    
protected:
    MemPool<STAFF_NOTE>  m_noteAlloc;
    STAFF_NOTE*  createNote();
    STAFF_NOTE_ARRAY m_noteArray;


private:
    midiCore *m_midi;
    MidiSystem  *m_midisystem[MAX_MIDI_TRACK];

    int m_trackCount;
    int m_speed;
    int m_tick;
    int m_clef;
    
    int m_TunePitch;
    int m_TuneType;
    
    int m_BeatNumerator;
    int m_BeatDenominator;
    
};

#endif /* MidiInterface_hpp */
