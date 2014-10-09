#ifndef __MainMenuScene_H__
#define __MainMenuScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCEGLView.h"
#include "InstructScene.h"
#include "MazeScene.h"
#include "SetScene.h"
#include "MainmenuScene.h"
#include "PopupLayer.h"
#include "TeachScene.h"

using namespace cocos2d;

class MainMenuScene :public CCLayer
{
public:
	//SCENE_NODE_FUNC(MainMenuScene);
	static CCScene * scene();
	bool init();
	void StartGame(CCObject * pSender);
	void ReInstruct(CCObject * pSender);
	void SetM(CCObject * pSender);
	void ExitM(CCObject * pSender);
	void Spring(CCObject * pSender);
	void Summer(CCObject * pSender);
	void Full(CCObject * pSender);
	void Winter(CCObject * pSsender);
	CCParticleSystem * particle;
	virtual void keyBackClicked();  //返回键回调函数

	CREATE_FUNC(MainMenuScene);
};
#endif