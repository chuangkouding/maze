#ifndef __DeadLayer_H__
#define __DeadLayer_H__


#include "cocos2d.h"
#include "MainmenuScene.h"
#include "MobClickCpp.h"
#include "MazeScene.h"

USING_NS_CC;
using namespace CocosDenshion;

class DeadLayer :public CCLayerColor
{
public:
	virtual bool init();
	static CCScene * scene();
	CREATE_FUNC(DeadLayer);
	void ReturnMain(CCObject * pSender);
	void Exit(CCObject * pSender);
	virtual void keyBackClicked();
};

#endif