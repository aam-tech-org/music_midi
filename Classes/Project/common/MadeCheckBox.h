#ifndef __MADE_CHECKBOX_H__
#define __MADE_CHECKBOX_H__

#pragma once
#include "2d/CCSprite.h"
#include "deprecated/CCDeprecated.h"
#include "cocos2d.h"

using namespace std;

USING_NS_CC;
typedef std::function<void(bool)> FUN_CLICK_LISTENER;

class MadeCheckBox :
	public cocos2d::Sprite
{
	
public:
	MadeCheckBox(const std::string& checked, const std::string& unchecked);
	
	static MadeCheckBox * create(const std::string& checked, const std::string& unchecked);

	virtual ~MadeCheckBox();

	virtual bool init();
	
	void setCheckedBackground(const std::string& checkedName, const std::string& uncheckedName);

	void setChecked(bool isChecked);

	bool getCheckedState();

	void setOnClickListener(FUN_CLICK_LISTENER listener);

private:
	bool isChecked = true;
	string checkedName, uncheckedName;
	FUN_CLICK_LISTENER listener;

	bool onTouchBegan(Touch* tTouch, Event* eEvent);//手指按下事件
	void onTouchMoved(Touch* tTouch, Event* eEvent);//手指移动事件
	void onTouchEnded(Touch* tTouch, Event* eEvent);//手指离开事件
};

#endif // __MADE_CHECKBOX_H__