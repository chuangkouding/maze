#ifndef __TeachScene_H__
#define __TeachScene_H__

#include "cocos2d.h"
#include "MazeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class TeachScene :public cocos2d::CCLayer
{
public:
	CREATE_FUNC(TeachScene);
	static CCScene * scene();
	bool init();
	void ReturnMainMenu(CCObject * sender);
	virtual void keyBackClicked();  //返回键回调函数
};
#endif