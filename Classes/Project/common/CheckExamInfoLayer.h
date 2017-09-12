//
// Created by hw on 2017/8/1.
//

#ifndef PROJ_ANDROID_STUDIO_CHECK_EXAM_INFO_LAYER_H
#define PROJ_ANDROID_STUDIO_CHECK_EXAM_INFO_LAYER_H


#include <ui/UIButton.h>
#include "cocos2d.h"
#include "string"

using namespace std;

USING_NS_CC;

class CheckExamInfoLayer : public LayerColor {
public:
	CheckExamInfoLayer();
    CheckExamInfoLayer(char *title, Layer *layer,
                       const string *button);

    ~CheckExamInfoLayer();

    virtual bool init();

    //touch事件监听 屏蔽向下触摸
    bool onTouchBegan(Touch *touch, Event *event);

    void onTouchMoved(Touch *touch, Event *event);

    void onTouchEnded(Touch *touch, Event *event);

    //点击事件回调接口
    void setNextClickCallback(Ref *target, SEL_CallFuncN callfun);

//    virtual void onEnter();
//
//    virtual void onExit();
//
//    void backgroundFinish();

    CREATE_FUNC(CheckExamInfoLayer);

private:
    void nextCallback(Ref *pSender);

    //标题
    Label *_m_title;
    //要显示的内容
    Layer *_m_contentLayer;
    //按钮
    ui::Button *_m_button;

//    //对话框大小
//    Size m_dialogContentSize;
//
//    Ref *m_callbackListener;
//
//    SEL_CallFuncN m_callback;
};

#endif //PROJ_ANDROID_STUDIO_CHECK_EXAM_INFO_LAYER_H
