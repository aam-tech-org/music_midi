#ifndef __WAVE_FORM_LAYER_H__
#define __WAVE_FORM_LAYER_H__

#include "cocos2d.h"
#include "ui/UILoadingBar.h"
#include "Project/core/midiCore/midiCore.h"

USING_NS_CC;
using namespace ui;

static const int _WAVE_FORM_HEIGHT_ = 414;

class WaveFormLayer : public cocos2d::Layer {
public:
    WaveFormLayer();

    ~WaveFormLayer();

    virtual bool init();
    void scheduleBlood(float delta);

    float getRate(int _level, ENUM_MIDI_VOICE_HEIGHT _emvh);

    CREATE_FUNC(WaveFormLayer);
private:
    DrawNode *_m_drawNode;
};

#endif // __WAVE_FORM_LAYER_H__
