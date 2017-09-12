//
// Created by hw on 2017/8/15.
//

#include "StaffNote.h"

MidiNoteSystem::NOTE StaffNote::getNote()
{
    return _note;
}

int StaffNote::getPageNumber()
{
    return _pageNumber;
}

string StaffNote::getLineName()
{
    return _lineName;
}

string StaffNote::getName()
{
    return _name;
}

void StaffNote::setNote(MidiNoteSystem::NOTE _note)
{
    this->_note = _note;
}

void StaffNote::setPageNumber(int _pageNumber)
{
    this->_pageNumber = _pageNumber;
}

void StaffNote::setLineName(string _lineName)
{
    this->_lineName = _lineName;
}

void StaffNote::setName(string _name)
{
    this->_name = _name;
}

void StaffNote::setLineFirst(bool _isFirst)
{
    _isLineFirst = _isFirst;
}

void StaffNote::setIsPageFirst(bool _isFirst)
{
    _isPageFirst = _isFirst;
}

bool StaffNote::isLineFirst()
{
    return _isLineFirst;
}

bool StaffNote::isPageFirst()
{
    return _isPageFirst;
}