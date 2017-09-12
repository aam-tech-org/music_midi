//
// Created by hw on 2017/7/31.
//

#ifndef PROJ_ANDROID_STUDIO_LOGINSCENE_H
#define PROJ_ANDROID_STUDIO_LOGINSCENE_H

#include "cocos2d.h"
#include <ui/UIEditBox/UIEditBox.h>

USING_NS_CC;

class LoginScene : public ::cocos2d::Scene {
public:
    LoginScene();

    ~LoginScene();

    ui::EditBox *_m_accountEeditText;
    ui::EditBox *_m_pwdEeditText;
    Sprite *_m_btnLogin;

    virtual bool init();

    CREATE_FUNC(LoginScene);
private:
    bool onTouchBegan(Touch *tTouch, Event *eEvent);//手指按下事件
    void onTouchMoved(Touch *tTouch, Event *eEvent);//手指移动事件
    void onTouchEnded(Touch *tTouch, Event *eEvent);//手指离开事件
};


#endif //PROJ_ANDROID_STUDIO_LOGINSCENE_H
