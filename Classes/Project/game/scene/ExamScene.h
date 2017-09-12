#ifndef __EXAM_SCENE_H__
#define __EXAM_SCENE_H__

#include "cocos2d.h"

class ExamScene : public cocos2d::Scene
{
public:
	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ExamScene);
};

#endif // __EXAM_SCENE_H__