#ifndef __NextMaze_H__
#define __NextMaze_H__

#include "cocos2d.h"
#include "MazeScene.h"

USING_NS_CC;

class NextMaze :public cocos2d::CCLayer
{
public:
	CREATE_FUNC(NextMaze);
	static CCScene * scene();
	bool init();
	void ReturnMainMenu(CCObject * sender);
};
#endif