//
//  MidiInterface.cpp
//  music_midi
//
//  Created by  fengrh on 2017/7/26.
//
//
#include "MidiInterface.h"


int MidiInterface::getNoteIndex(MIDI_BYTE bNote, int scale)
{
    int index = 0;
    switch(bNote % 12)
    {
        case 0:
            index  = ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 1:
            index  = ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 2:
            index  =  1 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 3:
            index  =  1 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 4:
            index  =  2 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 5:
            index  =  3 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 6:
            index  =  3 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 7:
            index  =  4 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 8:
            index  =  4 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 9:
            index  =  5 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 10:
            index  =  5 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
        case 11:
            index  =  6 + ((int)(bNote / 12)-2 - scale) * 7;
            break;
    }
    return index;
}


MidiInterface::MidiInterface(){
    
}

STAFF_NOTE* MidiInterface::createNote()
{
    STAFF_NOTE* _note = m_noteAlloc.create();
    memset(_note, 0, sizeof(STAFF_NOTE));
    return _note;
}


bool MidiInterface::init()
{
    m_midi = new midiCore;
    
    if (m_midi == NULL)
    {
        return false;
    }
    return true;
}


bool MidiInterface::release()
{
    for(unsigned int i=0; i< m_noteArray.size(); i++ )
    {
        STAFF_NOTE* _note = m_noteArray[i];
        
        if( _note )
        {
            m_noteAlloc.release(_note);
        }
    }
    
    m_noteArray.clear();
    
    
    if (m_midi != NULL)
    {
        delete m_midi;
    }
    
    for (int i = 0; i < m_trackCount; i++)
    {
        if (m_midisystem[i] != NULL)
        {
            m_midisystem[i]->clean();
            delete m_midisystem[i];
        }
    }
    return true;
}

   
int MidiInterface::loadMidi(const char* filename)
{
	int _nodeIndex[MAX_MIDI_TRACK];
    int _delayOfTrack[MAX_MIDI_TRACK];

    if(m_midi->load(filename))
    {
        m_midi->process();
       
        m_trackCount = m_midi->getTrackCount();

        for (int i = 0; i < m_trackCount; i++)
        {
            MIDI_TRACK *track = m_midi->getTrack(i);
            
            m_midisystem[i] = new MidiSystem;
            m_midisystem[i]->processTrack(track);
           
            _nodeIndex[i] = 0;
            _delayOfTrack[i] = 0;
            
        }
        
        int _totalIndex = 0;
        bool _beginTouch = false;
        
        
        int _pos = 0;
        int _noteIndex = 0;
        int _closeIndex = 0;
        while(1){
            bool _checkBreak = true;
            int  _delay = 0;
            
            if (_beginTouch)
            {
                if (_totalIndex < 100000)
                {
                    _totalIndex +=1;
                    continue;
                }
                else{
                    _totalIndex =0;
                }
            }
            
            for (int i = 0; i < m_trackCount; i++)
            {
                MIDI_NODE_ARRAY& _array = m_midisystem[i]->getList();
                
                if (_checkBreak && _nodeIndex[i] < _array.size())
                {
                    _checkBreak = false;
                }
                
                if (_nodeIndex[i] < _array.size())
                {
                    MIDI_NODE* _node = _array[_nodeIndex[i]];
                    if (_node->_delay != 0)
                    {
                        _delay = _node->_delay;
                    }
                    
                    bool _checkPlay = false;
                    
                    
                    if (_delayOfTrack[i] < _delay)
                    {
                        _delayOfTrack[i] += 1;
                    }
                    else
                    {
                        _delayOfTrack[i] = 0;
                        _checkPlay = true;
                    }
                    
                    if (_checkPlay)
                    {
                        _nodeIndex[i] += 1;
                        _pos += _node->_delay;

                        for (int j = 0; j < MAX_MIDI_EVENT_IN_NODE; j++)
                        {
                            const MIDI_EVENT* _midi_event = _node->_event[j];
                           
                            if (_midi_event != NULL)
                            {
                                MIDI_EVENT_NOTE* _midi_event_note = (MIDI_EVENT_NOTE*)_midi_event;
                                switch (_midi_event_note->_event) {
                                    case EME_OPENNOTE:
                                    {
                                       
                                        int _scale = _midi_event_note->_bNote / 12 - 2 ;
                                        if (_scale < 3  )
                                        {
                                           break;
                                        }
                                        
                                        if (_noteIndex > 0)
                                        {
                                            for(int i = _closeIndex; i < _noteIndex; i++)
                                            {
                                                STAFF_NOTE* _closeNote = m_noteArray[i];
                                                if ( _closeNote->_flag == 1)
                                                {
                                                    _closeNote->_endPos = _pos;
                                                    _closeNote->_flag = 2;
                                                }
                                            }
                                        }
                                        
                                        STAFF_NOTE* _note = createNote();
                                        m_noteArray.push_back(_note);
                                        _note->_beginPos = _pos;
                                        _note->_bNote = _midi_event_note->_bNote;
                                        _note->_bVel = _midi_event_note->_bVel;
                                        _note->_flag = 0;
                                        strcpy(_note->_szNote, _midi_event_note->getNoteName());
                                        
                                        _noteIndex++;
                                        
                                        break;
                                    }
                                    case EME_CLOSENOTE:
                                    {
                                        int _scale = _midi_event_note->_bNote / 12 - 2 ;
                                        if (_scale < 3  )
                                        {
                                            break;
                                        }
                                        
                                        
                                        for(int i = _closeIndex; i < _noteIndex; i++)
                                        {
                                            STAFF_NOTE* _closeNote = m_noteArray[i];
                                            
                                            if (int(_closeNote->_bNote) == int(_midi_event_note->_bNote) && _closeNote->_flag == 0)
                                            {
                                                _closeNote->_flag = 1;
                                            }
                                        }
                                        break;
                                    }
                                    case EME_CHANGEPROG:
                                    {
                                        
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
              
            }
            if (_checkBreak)
            {
                break;
            }
        }
        return 0;
    }else{
        return -1;
    }
 
}



MidiSystem* MidiInterface::getMidiData(int track)
{
    
    if ( track > m_trackCount)
    {
        return NULL;
    }
    return m_midisystem[track];
}



STAFF_NOTE_ARRAY& MidiInterface::getNoteList()
{
    return m_noteArray;
}


int MidiInterface::getTrackCount()
{
    return m_trackCount;
}

 


int MidiInterface::getTick()
{
    return m_tick;
}




void MidiInterface::CleanNote()
{
    for (unsigned int i = 0; i < m_noteArray.size(); i++)
    {
        if (int(m_noteArray[i]->_bNote)>65 + 24 && int(m_noteArray[i]->_bNote) < 65-24)
        {
        }
    }
}
 
 
 
