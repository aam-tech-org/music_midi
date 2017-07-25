
#ifndef MIDINOTATION_H
#define MIDINOTATION_H
typedef unsigned char BYTE;

enum MIDI_NOTATION_PITCH
{
	NOTATION_PITCH_C = 0,// C
	NOTATION_PITCH_SHARP_C,// C#
	NOTATION_PITCH_D,
	NOTATION_PITCH_SHARP_D,
	NOTATION_PITCH_E,
	NOTATION_PITCH_F,
	NOTATION_PITCH_SHARP_F,
	NOTATION_PITCH_G,
	NOTATION_PITCH_SHARP_G,
	NOTATION_PITCH_A,
	NOTATION_PITCH_SHARP_A,
	NOTATION_PITCH_B,

	EME_UNKNOWN,
};

class MidiNotation
{
	
public:
	MidiNotation();
	~MidiNotation();
	int getDynamics();
	int getMusicaScale();
	BYTE getPitch();
	

private:
	int _nDynamic;//力度
	int _nMusicalScale;//音阶
	BYTE _ePitch;//音调
};



MidiNotation::MidiNotation()
{
}

MidiNotation::~MidiNotation()
{
}


#endif /* APPSHADER_H */
