#include "RenewScene.h"


CCScene * RenewScene::scene()
{
	CCScene * scene = CCScene::create();
	RenewScene * layer = RenewScene::create();
	scene->addChild(layer);
	return scene;
}
bool RenewScene::init()
{
	bool bRet = false;
	do
	{
		//CC_BREAK_IF(!CCLayer::init);
		setKeypadEnabled(true);
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLayerColor * layerColor = CCLayerColor::create(ccc4(224, 255, 255, 255));
		this->addChild(layerColor, 0);

		CCSprite  * BackGround = CCSprite::create("StartGB.png");
		BackGround->setPosition(ccp(origin.x + visibleSize.width / 2,//- BackGround->getContentSize().width / 2,
			origin.y + visibleSize.height / 2)); // 2 //- BackGround->getContentSize().height / 2));
		this->addChild(BackGround, 1);
		/*以下是各张地图的重新载入先写一张地图按钮放着,之后定义地图按钮是否显示然后不同地图对应不同的数字然后进行相应的设置*/
		CCMenuItemImage * MazeBottom1 = CCMenuItemImage::create(
			"cspring.png",
			"cspring2.png",
			this,
			menu_selector(RenewScene::RenewGame1)); ///////////////////////

		MazeBottom1->setPosition(ccp(origin.x + visibleSize.width * (1.0/5) - MazeBottom1->getContentSize().width / 2,
			origin.y +visibleSize.height*(1.0/4) /* MazeBottom1->getContentSize().height / 2*/));

		CCMenuItemImage * MazeBottom2 = CCMenuItemImage::create(
			"csummer.png",
			"csummer2.png",
			this,
			menu_selector(RenewScene::RenewGame2)); ///////////////////////

		MazeBottom2->setPosition(ccp(origin.x + visibleSize.width * (1.0/2) - MazeBottom2->getContentSize().width ,
			origin.y + visibleSize.height*(1.0 / 2) + MazeBottom2->getContentSize().height / 2));

		CCMenuItemImage * MazeBottom3 = CCMenuItemImage::create(
			"cautumn.png",
			"cautumn2.png",
			this,
			menu_selector(RenewScene::RenewGame3)); ///////////////////////

		MazeBottom3->setPosition(ccp(origin.x + visibleSize.width * (4.0 / 9) + MazeBottom3->getContentSize().width ,
			origin.y + visibleSize.height*(1.0 / 6) + MazeBottom3->getContentSize().height*2 ));

		CCMenuItemImage * MazeBottom4 = CCMenuItemImage::create(
			"cwinter.png",
			"cwinter2.png",
			this,
			menu_selector(RenewScene::RenewGame4)); ///////////////////////

		MazeBottom4->setPosition(ccp(origin.x + visibleSize.width * (5.0 / 9) + MazeBottom4->getContentSize().width*2 ,
			origin.y + visibleSize.height*(1.0 / 2) + MazeBottom4->getContentSize().height/7 ));

		CCMenuItemImage * ReturnBottom = CCMenuItemImage::create(
			"Renew1.png",
			"Renew2.png",
			this,
			menu_selector(RenewScene::ReturnSet));////

		ReturnBottom->setPosition(ccp(origin.x + visibleSize.width - ReturnBottom->getContentSize().width / 2,
			origin.y + ReturnBottom->getContentSize().height / 2));


		CCMenu * pMenu = CCMenu::create(MazeBottom1, MazeBottom2, MazeBottom3, MazeBottom4,ReturnBottom, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 2);
		bRet = true;
	} while (0);
	return bRet;
}

void RenewScene::RenewGame1(CCObject * pSender)
{
	fun();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("RenewCount", 1);
	CCUserDefault::sharedUserDefault()->flush();
	RenewLayer * poplayer = RenewLayer::create();
	this->addChild(poplayer,4);
}
void RenewScene::RenewGame2(CCObject * pSender)
{
	fun();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("RenewCount", 2);
	CCUserDefault::sharedUserDefault()->flush();
	if (maxCount >= 2)
	{
		RenewLayer * poplayer = RenewLayer::create();
		this->addChild(poplayer, 4);
	}
	else
	{
		CCLayer * layer = NGLayer::create();
		this->addChild(layer, 4);
	}
}
void RenewScene::RenewGame3(CCObject * pSender)
{
	fun();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("RenewCount", 3);
	CCUserDefault::sharedUserDefault()->flush();
	if (maxCount >= 3)
	{
		RenewLayer * poplayer = RenewLayer::create();
		this->addChild(poplayer, 4);
	}
	else
	{
		CCLayer * layer = NGLayer::create();
		this->addChild(layer, 4);
	}
}
void RenewScene::RenewGame4(CCObject * pSender)
{
	fun();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("RenewCount", 4);
	CCUserDefault::sharedUserDefault()->flush();
	if (maxCount >= 4)
	{
		RenewLayer * poplayer = RenewLayer::create();
		this->addChild(poplayer, 4);
	}
	else
	{
		CCLayer * layer = NGLayer::create();
		this->addChild(layer, 4);
	}
}
void RenewScene::ReturnSet(CCObject * pSender)
{
	CCScene * set = SetScene::scene();
	CCDirector::sharedDirector()->replaceScene(set);
}
void RenewScene::fun()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxCount", 4); //youyuceshi
	if (!CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxCount"))
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxCount", 1);
	}
	maxCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxCount");
}
void RenewScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(SetScene::scene());
}