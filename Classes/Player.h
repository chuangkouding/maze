#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
//#include "PositionController.h"
USING_NS_CC;
class Player:public CCNode
{
public:
	~Player();
	virtual bool init(); //��ʼ������
	void bindSprite(CCSprite * Sprite);
	void run(int x);
	void stop();
	CCSize getSpriteSize();
	CREATE_FUNC(Player);
protected:
	bool m_isRunning;
	CCSprite *m_sprite; //�󶨵Ķ���
	CCAnimate *m_animate[4]; //��ǰ����
	int m_direction;
	CCSpriteFrameCache *m_frameCache;
//	PositionController *positionController;
};


#endif // !__PLAYER_H__

