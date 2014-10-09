#include "NextMaze.h"

int ct;
float nextPosition[4][2] = { 72, 2376, 1376, 5850, 4488, 696, 72, 2616 };

CCScene * NextMaze::scene()
{
	CCScene * scene = CCScene::create();
	NextMaze * layer = NextMaze::create();
	scene->addChild(layer);
	return scene;
}
bool NextMaze::init()
{
	bool bRet = false;
	do
	{
		ct = 0;
		//CC_BREAK_IF(!CCLayer::init);
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLayerColor * layerColor = CCLayerColor::create(ccc4(224, 255, 255, 255));
		this->addChild(layerColor, 0);

		int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("Count");

		CCSprite  * BackGround = CCSprite::create(CCString::createWithFormat("funEnd_%d.png", count)->getCString());
		BackGround->setPosition(ccp(origin.x + visibleSize.width / 2,//- BackGround->getContentSize().width / 2,
			origin.y + visibleSize.height / 2)); // 2 //- BackGround->getContentSize().height / 2));
		this->addChild(BackGround, 1);

		CCMenuItemImage * ReturnBottom = CCMenuItemImage::create(
			"next_bottom1.png",
			"next_bottom2.png",
			this,
			menu_selector(NextMaze::ReturnMainMenu));

		ReturnBottom->setPosition(ccp(origin.x + visibleSize.height-ReturnBottom->getContentSize().width / 2,
			origin.y +  ReturnBottom->getContentSize().height / 2));

		CCMenu * pMenu = CCMenu::create(ReturnBottom, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 4);
		bRet = true;
	} while (0);
	return bRet;
}

void NextMaze::ReturnMainMenu(CCObject * sender)
{
	ct++;
	if (ct == 1)
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("Count");

		CCSprite * sprite = CCSprite::create(CCString::createWithFormat("next_teach_%d.png", count)->getCString());
		//sprite->setPosition(ccp(orign.x, orign.y));
		sprite->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(sprite, 3);
		CCScaleTo * scaleTo = CCScaleTo::create(0.1f, 0.1f, 0.1f);
		sprite->runAction(scaleTo);
		CCScaleTo * scaleTo1 = CCScaleTo::create(2.9f, 1.0f, 1.0f);
		sprite->runAction(scaleTo1);
	}
	else if(ct == 2)
	{
		int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("Count");
		int maxCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxCount");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("IsFood", 0);
		CCUserDefault::sharedUserDefault()->flush();
		for (int i = 0; i < 50; i++)
		{
			CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("foo3_%d", i)->getCString(), 1);
			CCUserDefault::sharedUserDefault()->flush();
		}
		CCScene * pScene;
		if (count < 4)
		{
			/*if (count == 1)
			{
				CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 1400 - 24);//暂时，夏天迷宫的初始位置
				CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 5880);
				CCUserDefault::sharedUserDefault()->flush();
			}
			else if (count == 2)
			{
				CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 4512 - 24);//暂时，秋天迷宫的初始位置
				CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 720 - 24);
				CCUserDefault::sharedUserDefault()->flush();
			}
			else if (count == 3)
			{
				CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 96 - 24);//暂时，冬天迷宫的初始位置
				CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 2640 - 24);
				CCUserDefault::sharedUserDefault()->flush();
			}*/
			CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", nextPosition[count][0]);
			CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", nextPosition[count][1]);
			CCUserDefault::sharedUserDefault()->flush();
			count++;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("Count", count);
			CCUserDefault::sharedUserDefault()->flush();
			if (count > maxCount)
			{
				maxCount = count;
				CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxCount", maxCount);
				CCUserDefault::sharedUserDefault()->flush();
			}
			pScene = MazeScene::create();
		}
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}