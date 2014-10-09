#ifndef __PopupLayer_H__
#define __PopupLayer_H__


#include "cocos2d.h"
#include "MainmenuScene.h"
#include "PopupLayer.h"

USING_NS_CC;

class PopupLayer :public CCLayerColor
{
private:
	CCMenu * m_pMenu;
	bool m_bTouchedMenu;
public:
	char picture[20];
	virtual bool init();
	CREATE_FUNC(PopupLayer);
	void onEnter();
	void onExit();

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
	virtual void keyBackClicked();  //返回键回调函数

	void Confirm(CCObject * pSender);
	void fun();
};

#endif