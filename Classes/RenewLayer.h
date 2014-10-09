#ifndef __RenewLayer_H__
#define __RenewLayer_H__


#include "cocos2d.h"
#include "MazeScene.h"

USING_NS_CC;

class RenewLayer :public CCLayerColor
{
private:
	CCMenu * m_pMenu;
	bool m_bTouchedMenu;
public:
	virtual bool init();
	CREATE_FUNC(RenewLayer);

	void onEnter();
	void onExit();

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
	virtual void keyBackClicked();  //返回键回调函数
	void Exit(CCObject * pSender);
	void RenewGame(CCObject * pSender);
	void StartGame();//动作监听的回调函数
};
#endif