//
// Created by hw on 2017/8/2.
//

#ifndef PROJ_ANDROID_STUDIO_MADEBUTTON_H
#define PROJ_ANDROID_STUDIO_MADEBUTTON_H

#include "cocos2d.h"
#include "string"

using namespace std;

USING_NS_CC;
class MadeButton : public Layer {
public:
	MadeButton();
	~MadeButton();
	void setBackground(string normal, string pressed);
    

private:
	//Size _m_size;//按钮大小
	string _m_normalName;//默认图片
	string _m_pressedName;//按压图片
	//Size _m_size;//按钮大小
	int _m_fontSize;//文字颜色
	Label l;
	
};


#endif //PROJ_ANDROID_STUDIO_MADEBUTTON_H
