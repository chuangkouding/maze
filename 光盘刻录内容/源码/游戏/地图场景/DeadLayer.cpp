#include "DeadLayer.h"


CCScene * DeadLayer::scene()
{
	CCScene * scene = CCScene::create();
	DeadLayer * layer = DeadLayer::create();
	scene->addChild(layer);
	return scene;
}

bool DeadLayer::init()
{

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 50)));
		setKeypadEnabled(true);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 4512 - 24);//秋天
		CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 720 - 24);
		CCUserDefault::sharedUserDefault()->flush();

		for (int i = 0; i < 9; i++)  //初始化道具显示啥的
		{
			CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveF_%d", i)->getCString(), 1);
			CCUserDefault::sharedUserDefault()->flush();
		}

		CCSprite * background = CCSprite::create("Deadpic.png");
		background->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(background);
		CCMenuItemImage * ReturnMBottom = CCMenuItemImage::create(
			"FreturnMain1.png",
			"FreturnMain2.png",
			this,
			menu_selector(DeadLayer::ReturnMain));
		ReturnMBottom->setPosition(ccp(origin.x /*+ visibleSize.width / 2*/ + ReturnMBottom->getContentSize().width / 2,
			origin.y /*+ visibleSize.height / 2 */+ ReturnMBottom->getContentSize().height / 2));

		CCMenuItemImage * ExitBottom = CCMenuItemImage::create(
			"Restartthis1.png",
			"Restartthis2.png",
			this,
			menu_selector(DeadLayer::Exit));
		ExitBottom->setPosition(ccp(origin.x + visibleSize.width  - ExitBottom->getContentSize().width / 2,
			origin.y /*+ visibleSize.height / 2 */+ ExitBottom->getContentSize().height / 2));

		CCMenu * m_pMenu = CCMenu::create(ReturnMBottom, ExitBottom, NULL);
		m_pMenu->setPosition(CCPointZero);

		this->addChild(m_pMenu);
		bRet = true;
	} while (0);
	return bRet;
}

void DeadLayer::Exit(CCObject * pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MazeScene::create(), ccc3(255, 255, 255)));
}

void DeadLayer::ReturnMain(CCObject * pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MainMenuScene::scene(), ccc3(255, 255, 255)));
}
void DeadLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MazeScene::create(), ccc3(255, 255, 255)));
}