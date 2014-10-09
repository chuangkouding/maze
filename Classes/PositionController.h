#ifndef __POSITIONCONTROLLER_H__
#define __POSITIONCONTROLLER_H__	

#include "cocos2d.h"
#include "Player.h"
#include "final2.h"
#include "Math.h"
#include <string.h>
#include "NextMaze.h"
#include "MazeScene.h"
#include "DeadLayer.h"

USING_NS_CC;


class PositionController :public CCLayer
{
public:
	virtual bool init();
	void update(float dt);
	void setListenPlayer(Player *player);
	void setListenMap(CCTMXTiledMap *map);
	void setiXSpeed(float iSpeed);
	void setiYSpeed(float iSpeed);
	void setViewPointByPlayer();
	void setRocker_bg(CCSprite *rocker_bg);
	void setRocker(CCSprite *rocker);
	void setMenuLayer(CCLayer *menuLayer);
	void setMazeSceneKeypad(CCKeypadDelegate *mazeSceneKeypad);

	//void setPlayerPositionOnMap(CCPoint pos);
	CCPoint getPlayerPositionOnMap();
	
	CREATE_FUNC(PositionController);
	//´¥ÆÁÊÂ¼þ
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);
	void display(int &question1, CCDictionary * propertiesDict,const CCString* prop,string str,const char * str2);
	void display1(int &question1, CCDictionary * propertiesDict, const CCString* prop, string str, const char * str2, const char *str3, int &gua, int x, int y);
	void display_NPC(int &question1, CCDictionary * propertiesDict, const CCString* prop, const char * str, const char * str2);
private:
	CCPoint tileCoordForPosition(CCPoint pos);
	CCKeypadDelegate *m_mazeSceneKeypad;
	Player *m_player;
	CCTMXTiledMap *m_map;
	CCTMXLayer * meta;
	float m_iXSpeed;
	float m_iYSpeed;
	const static int m_PlayerMaxSpeed = 5;
	CCSprite *m_rocker_bg;
	CCSprite *m_rocker;
	CCLayer *m_menuLayer;
	
};
#endif // !__POSITIONCONTROLLER_H__
