#ifndef __PopLayer_H__
#define __PopLayer_H__


#include "cocos2d.h"
#include "MainmenuScene.h"
#include "MobClickCpp.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class PopLayer :public CCLayerColor
{
private:
	CCMenu * m_pMenu;
	bool m_bTouchedMenu;
	CCKeypadDelegate *m_MazeKey;
public:
	char str[20];
	virtual bool init();
	CREATE_FUNC(PopLayer);
	void onEnter();
	void onExit();

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
	virtual void keyBackClicked();  //返回键回调函数

	void setMazeKey(CCKeypadDelegate * d);
	void ReturnGame(CCObject * pSender);
	void PauseMusic(CCObject * pSender);
	void ReturnMain(CCObject * pSender);
	void fun();
	void Exit(CCObject * pSender);
};

#endif