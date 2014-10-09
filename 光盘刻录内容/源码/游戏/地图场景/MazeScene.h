#ifndef __MAZESCENE_H__
#define __MAZESCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "PopLayer.h"
#include "PositionController.h"
#include "PopupLayer.h"

USING_NS_CC;

class MazeScene : public cocos2d::CCScene, public CCKeypadDelegate
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	//static cocos2d::CCScene* scene();
	void menuSoundSettingCallback(CCObject* pSender);		
	//void ReturnMainMenu(CCObject * sender);				//返回主菜单用
	bool isHaveSaveFile();						//检查是否有存档
	
	virtual void keyBackClicked();  //返回键回调函数
	CREATE_FUNC(MazeScene);
	MazeScene();
protected:
	Player* m_Player;
	CCTMXTiledMap *m_map;
	//static bool IsSaveExist;
};

#endif // __HELLOWORLD_SCENE_H__
