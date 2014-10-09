#include "RenewLayer.h"

float initPosition[4][2] = {72,2376,1376,5850,4488,696,72,2616};
char iPicture[4][20] = { "teach_6.png","next_teach_1.png", "next_teach_2.png","next_teach_3.png"};

bool RenewLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
		m_pMenu = NULL;
		setKeypadEnabled(true);
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		
		CCSprite * sprite = CCSprite::create("RenewSprite.png");//背景要设成透明图层
		sprite->setPosition(ccp(origin.x + visibleSize.width*(11.0 / 24), origin.y + visibleSize.height*(2.0 / 3)));
		this->addChild(sprite);

		CCMenuItemImage * RenewGBottom = CCMenuItemImage::create(
			"SRenew1.png",
			"SRenew2.png",
			this,
			menu_selector(RenewLayer::RenewGame));

		RenewGBottom->setPosition(ccp(origin.x + visibleSize.width*(3.0 / 7) - RenewGBottom->getContentSize().width / 2
			, origin.y + visibleSize.height*(2.0 / 5) - RenewGBottom->getContentSize().height / 2));

		CCMenuItemImage * ExitBottom = CCMenuItemImage::create(
			"RRenew1.png",
			"RRenew2.png",
			this,
			menu_selector(RenewLayer::Exit));

		ExitBottom->setPosition(ccp(origin.x + visibleSize.width*(5.0 / 7) - ExitBottom->getContentSize().width / 2
			, origin.y + visibleSize.height*(2.0 / 5) - ExitBottom ->getContentSize().height / 2));

		m_pMenu = CCMenu::create(RenewGBottom, ExitBottom, NULL);

		m_pMenu->setPosition(CCPointZero);

		this->addChild(m_pMenu,2);

		bRet = true;
	} while (0);
	return bRet;
}

void RenewLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, kCCMenuHandlerPriority - 1, true);
	/*CCDirector::sharedDispatcher()->addTargetedDelegate(this,
	kCCMenuTouchPriority - 1, true);*/
}
void RenewLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool RenewLayer::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_pMenu != NULL)
		m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
	return true;
}
void RenewLayer::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		if (m_pMenu != NULL)
			m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}
void RenewLayer::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		if (m_pMenu != NULL)
			m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}
void RenewLayer::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		if (m_pMenu != NULL)
			m_pMenu->ccTouchCancelled(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}
/*在下面这个函数进行重新开始的初始化，然后之前的按钮都会指向这张图然后传参决定出现哪张地图*/
void RenewLayer::RenewGame(CCObject * pSender) 
{
	int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("RenewCount");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Count", count);
	CCUserDefault::sharedUserDefault()->flush();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("IsFood", 0);
	CCUserDefault::sharedUserDefault()->flush();
	for (int i = 0; i < 4; i++)  //初始化道具显示啥的
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveS_%d", i)->getCString(), 1);
		CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("NPCS_%d", i + 1)->getCString(), 0);
		CCUserDefault::sharedUserDefault()->flush();
	}
	for (int i = 0; i < 9; i++)  //初始化道具显示啥的
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("NPCF_%d", i + 1)->getCString(), 0);
		CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveF_%d", i)->getCString(), 1);
		CCUserDefault::sharedUserDefault()->flush();
	}
	CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", initPosition[count-1][0]);
	CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", initPosition[count - 1][1]);
	CCUserDefault::sharedUserDefault()->flush();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	this->removeChild(m_pMenu);
	m_pMenu = NULL;
	CCSprite * sprite = CCSprite::create(CCString::createWithFormat("%s", iPicture[count-1])->getCString());
	sprite->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(sprite, 3);
	//CCScaleTo * scaleTo = CCScaleTo::create(0.1f, 0.1f, 0.1f);
	//sprite->runAction(scaleTo);
	CCScaleTo * scaleTo1 = CCScaleTo::create(4.0f, 1.0f, 1.0f);
	//sprite->runAction(scaleTo1);
	CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(RenewLayer::StartGame));
	CCSequence * action = CCSequence::create(scaleTo1,callFunc, NULL);
	sprite->runAction(action);
}
void RenewLayer::Exit(CCObject * pSender)
{
	this->removeFromParentAndCleanup(false);
}
void RenewLayer::StartGame()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, MazeScene::create()));
}
void RenewLayer::keyBackClicked()
{
	this->removeFromParentAndCleanup(false);
}
