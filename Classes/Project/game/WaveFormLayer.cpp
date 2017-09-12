#include "WaveFormLayer.h"
#include "Project/common/MidiDriver.h"
#include "Project/common/ExamMidiSystem.h"
#include "Project/common/MadeFileUtils.h"
#include "math.h"

WaveFormLayer::WaveFormLayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("staff.plist", "staff.pvr.ccz");
}

WaveFormLayer::~WaveFormLayer()
{
}

bool WaveFormLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    setContentSize(Size(visibleSize.width, _WAVE_FORM_HEIGHT_));
    setPosition(Point(origin.x, origin.y + visibleSize.height - _WAVE_FORM_HEIGHT_));
    setAnchorPoint(Point::ZERO);

    LoadingBar *_loadingBar = LoadingBar::create("staff_loading_progress.png",
                                                 ui::Widget::TextureResType::PLIST, 100);
    _loadingBar->setAnchorPoint(Point::ZERO);
    _loadingBar->setPosition(Point::ZERO);
    _loadingBar->setContentSize(Size(visibleSize.width, 20));
    addChild(_loadingBar);

//    Sprite *_bgSprite = Sprite::createWithSpriteFrameName("staff_loading_bg.png");
//    _bgSprite->setAnchorPoint(Point::ZERO);
//    _bgSprite->setContentSize(Size(visibleSize.width, 20));
//    addChild(_bgSprite);
//
//    Sprite *_progressSprite = Sprite::createWithSpriteFrameName("staff_loading_progress.png");
//    _bgSprite->setAnchorPoint(Point::ZERO);
//    _bgSprite->setContentSize(Size(visibleSize.width, 20));
//    addChild(_progressSprite);
//
//    ProgressTimer *_progressTimer = ProgressTimer::create(_progressSprite);
//    _progressTimer->setType(ProgressTimer::Type::BAR);
//    _progressTimer->setPosition(Point::ZERO);
//    _progressTimer->setMidpoint(Point(1, 0.5f));
//    _progressTimer->setBarChangeRate(Point(1, 0));
//    _progressTimer->setTag(1024);
//    _progressTimer->setContentSize(Size(visibleSize.width, 20));
//    addChild(_progressTimer);
//    schedule(schedule_selector(WaveFormLayer::scheduleBlood), 0.1f);


    Sprite *_sprite = Sprite::createWithSpriteFrameName("wave_form_bg.png");
    _sprite->setAnchorPoint(Point::ZERO);
    _sprite->setPosition(Point(0, 20));
    _sprite->setContentSize(Size(visibleSize.width, 394));
    addChild(_sprite);

    DrawNode *drawNode = DrawNode::create(1);
    drawNode->setAnchorPoint(Point::ZERO);
    addChild(drawNode);

    drawNode->setLineWidth(1);
    drawNode->drawLine(Point(20, 0), Point(20, 200), Color4F(Color4B(56, 198, 199, 255)));

//    _m_drawNode = DrawNode::create(2);
//    _m_drawNode->setAnchorPoint(Point::ZERO);

//    int x = 21;
//    for (int i = 0; i < 100; i++) {
//        int x = 21 + i * 4 + 1;
//        Point form = Point(x, 160);
//        Point to = Point(x, 160 + i + 10);
//        _m_drawNode->drawLine(form, to, Color4F(Color4B(75, 78, 95, 255)));
//        CCLOG("********  i= %d  *************", i);
//        CCLOG("********  x= %d  *************", x);
//        Sprite *sprite = Sprite::createWithSpriteFrameName("icon_wave_form.png");
//        sprite->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//        sprite->setContentSize(Size(4, 160 + i + 10));
//        sprite->setPosition(Point(x, 160));
//        addChild(sprite);
//        x += 6;
//    }

//    ExamMidiSystem _examMidiSystem;
//    MadeFileUtils madeFileUtils;
//    std::string path = madeFileUtils.copyFile("test1.mid");
//    _examMidiSystem.loadFile(path.c_str());
//    _examMidiSystem.process();
//    STAFF_NOTE_ARRAY _midiNodeArray = _examMidiSystem.getMidiNodeArray();
//    int x = 22;
//    for (int i = 0; i < _midiNodeArray.size(); i++)
//    {
//        StaffNote _staffNote = _midiNodeArray.at(i);
//        MidiNoteSystem::NOTE _note = _staffNote.getNote();
//        float _height = getRate(_note.getLevel(), _note.getHeight()) / 987.77 * 260.0;
//        float y = 160 - _height * 0.5;
//        Point form(x, y);
//        Point to(x, y + _height);
//        _m_drawNode->drawSegment(form, to,0.5, Color4F(Color4B(75, 78, 95, 255)));
//        x += 8;
//    }
//    addChild(_m_drawNode);
    return true;
}

void WaveFormLayer::scheduleBlood(float delta)
{
    ProgressTimer *progress = (ProgressTimer *) this->getChildByTag(1024);
    progress->setPercentage(50);  //这里是百分制显示
    if (progress->getPercentage() < 0)
    {
        this->unschedule(schedule_selector(WaveFormLayer::scheduleBlood));
    }
}

float WaveFormLayer::getRate(int _level, ENUM_MIDI_VOICE_HEIGHT _emvh)
{
    float _rate;
    if (_level == 4)
    {
        _rate = 130.81;
    } else if (_level == 5)
    {
        _rate = 261.63;
    } else if (_level == 6)
    {
        _rate = 523.25;
    }

    int _e = EMVH_C;
    for (; _e <= EMVN_B; _e++)
    {
        if (_e == _emvh)
        {
            break;
        }
        _rate = _rate * 1.05946;
    }

    int tmp = (_rate + 0.005) * 100;//保留两位小数
    _rate = tmp / 100;
    return _rate;
}
