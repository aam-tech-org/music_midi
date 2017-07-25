#include "MidiNotation.h"

int MidiNotation::getDynamics() 
{
	return _nDynamic;
}

int MidiNotation::getMusicaScale()
{
	return _nMusicalScale;
}

BYTE MidiNotation::getPitch() {
	return _ePitch;
}