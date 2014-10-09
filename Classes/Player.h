#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
//#include "PositionController.h"
USING_NS_CC;
class Player:public CCNode
{
public:
	~Player();
	virtual bool init(); //初始化函数
	void bindSprite(CCSprite * Sprite);
	void run(int x);
	void stop();
	CCSize getSpriteSize();
	CREATE_FUNC(Player);
protected:
	bool m_isRunning;
	CCSprite *m_sprite; //绑定的对象
	CCAnimate *m_animate[4]; //当前动画
	int m_direction;
	CCSpriteFrameCache *m_frameCache;
//	PositionController *positionController;
};


#endif // !__PLAYER_H__

