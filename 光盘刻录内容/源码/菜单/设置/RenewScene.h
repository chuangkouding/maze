#ifndef __StartG_H__
#define __StartG_H__

#include "cocos2d.h"
#include "RenewLayer.h"
#include "SetScene.h"
#include "NGLayer.h"

USING_NS_CC;

class RenewScene :public cocos2d::CCLayer
{
public:
	CREATE_FUNC(RenewScene);
	static CCScene * scene();
	bool init();
	
	void RenewGame1(CCObject * pSender);
	void RenewGame2(CCObject * pSender);
	void RenewGame3(CCObject * pSender);
	void RenewGame4(CCObject * pSender);
	void ReturnSet(CCObject * pSender);
	virtual void keyBackClicked();  //返回键回调函数
	int maxCount;
	void fun();
};
#endif