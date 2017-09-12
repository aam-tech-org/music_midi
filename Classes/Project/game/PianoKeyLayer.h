#ifndef __PIANO_KEY_LAYER_H__
#define __PIANO_KEY_LAYER_H__

#include "cocos2d.h"
#include <ui/UICheckBox.h>
#include "Project/common/MidiDriver.h"

USING_NS_CC;
using namespace ui;

class PianoKeyLayer :public cocos2d::Layer
{
public:
	PianoKeyLayer();
	~PianoKeyLayer();
//	void onClick(bool isChecked);
	void onClick(Ref* pSender, CheckBox::EventType type);
	virtual bool init();

	CREATE_FUNC(PianoKeyLayer);

private:
	cocos2d::Sprite *_m_pianoSprite;
	CheckBox *_m_checkbox;
    Size _m_visibleSize;
    float _m_fPianoKeyHeight;
	MidiDriver midiDriver;

};

#endif //__PIANO_KEY_LAYER_H__

