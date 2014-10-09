#ifndef __SetScene_H__
#define __SetScene_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainmenuScene.h"
#include "SimpleAudioEngine.h"
#include "RenewScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SetScene :public CCLayer
{
public:
	static CCScene * scene();
	bool init();
	void ReturnMainMenu(CCObject * sender);
	void RenewGame(CCObject * sender);
	CREATE_FUNC(SetScene);
	void BackMC(CCObject* pSender, CCControlEvent event);
	void BackEC(CCObject * pSender, CCControlEvent event);
	virtual void keyBackClicked();  //返回键回调函数
private:
	CCControlSwitch *m_backgroundSwitch;
	CCControlSwitch *m_effectSwitch;
	CCParticleSystem * particle;
};

#endif