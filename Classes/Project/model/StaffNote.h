//
// Created by hw on 2017/8/15.
//

#ifndef PROJ_ANDROID_STUDIO_STAFFNOTE_H
#define PROJ_ANDROID_STUDIO_STAFFNOTE_H

#include "Project/core/staffCore/staffSymbol.h"
#include "Project/core/midiCore/midiCore.h"

class StaffNote
{
public:
    MidiNoteSystem::NOTE getNote();

    int getPageNumber();

    string getLineName();

    string getName();

    void setNote(MidiNoteSystem::NOTE note);

    void setPageNumber(int pagerNumber);

    void setLineName(string _lineName);

    void setName(string _name);

    void setLineFirst(bool _isFirst);

    void setIsPageFirst(bool _isFirst);

    bool isLineFirst();

    bool isPageFirst();

private:
    int _pageNumber;
    string _lineName;
    string _name;
    bool _isLineFirst, _isPageFirst;
    MidiNoteSystem::NOTE _note;
};


#endif //PROJ_ANDROID_STUDIO_STAFFNOTE_H
