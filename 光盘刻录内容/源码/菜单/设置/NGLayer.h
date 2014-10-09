#ifndef __NGLayer_H__
#define __NGLayer_H__


#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class NGLayer :public CCLayerColor
{
private:
	CCMenu * m_pMenu;
	bool m_bTouchedMenu;
public:
	virtual bool init();
	CREATE_FUNC(NGLayer);

	void onEnter();
	void onExit();

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);

	void Exit(CCObject * pSender);
};
#endif