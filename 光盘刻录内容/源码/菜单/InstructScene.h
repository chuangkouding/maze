#ifndef __InstructScene_H__
#define __InstructScene_H__

#include "cocos2d.h"
#include "MainmenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class InstructScene :public cocos2d::CCLayer
{
public:
	CREATE_FUNC(InstructScene);
	static CCScene * scene();
	bool init();
	void ReturnMainMenu(CCObject * sender);
	virtual void keyBackClicked();  //返回键回调函数
};
#endif