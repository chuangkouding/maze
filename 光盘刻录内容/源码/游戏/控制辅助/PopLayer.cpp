#include "PopLayer.h"


bool PopLayer::init()
{
	
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 50)));
		//setKeypadEnabled(true);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSprite * background = CCSprite::create("HelloWorld.png");
		background->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(background);
		CCMenuItemImage * ReturnGBottom = CCMenuItemImage::create(
			"ReturnGame1.png",
			"ReturnGame2.png",
			this,
			menu_selector(PopLayer::ReturnGame));
		ReturnGBottom->setPosition(ccp(origin.x + visibleSize.width / 2 - ReturnGBottom->getContentSize().width / 2,
			origin.y + visibleSize.height / 2 + ReturnGBottom->getContentSize().height / 2));

		CCSprite * spriteLogo = CCSprite::create("QLlogo.png");
		spriteLogo->setPosition(ccp(origin.x + visibleSize.width - spriteLogo->getContentSize().width / 2, origin.y + visibleSize.height*0.94));
		this->addChild(spriteLogo, 7);
		CCFadeOut * fadeOut = CCFadeOut::create(6.0f);
		CCRepeatForever * repeateForever1 = CCRepeatForever::create(fadeOut);
		spriteLogo->runAction(repeateForever1);

		CCMenuItemImage * PauseMBottom = CCMenuItemImage::create(
			"PauseMusic1.png",
			"PauseMusic2.png",
			this,
			menu_selector(PopLayer::PauseMusic));
		PauseMBottom->setPosition(ccp(origin.x + visibleSize.width / 2 + PauseMBottom->getContentSize().width / 2,
			origin.y + visibleSize.height / 2 + PauseMBottom->getContentSize().height / 2));

		CCMenuItemImage * ReturnMBottom = CCMenuItemImage::create(
			"GReturnMain1.png",
			"GReturnMain2.png",
			this,
			menu_selector(PopLayer::ReturnMain));
		ReturnMBottom->setPosition(ccp(origin.x + visibleSize.width / 2 - ReturnMBottom->getContentSize().width / 2,
			origin.y + visibleSize.height / 2 - ReturnMBottom->getContentSize().height / 2));

		CCMenuItemImage * ExitBottom = CCMenuItemImage::create(
			"ExitGame1.png",
			"ExitGame2.png",
			this,
			menu_selector(PopLayer::Exit));
		ExitBottom->setPosition(ccp(origin.x + visibleSize.width / 2 + ExitBottom->getContentSize().width / 2,
			origin.y + visibleSize.height / 2 - ExitBottom->getContentSize().height / 2));

		m_pMenu = CCMenu::create(ReturnGBottom, PauseMBottom, ReturnMBottom, ExitBottom, NULL);
		m_pMenu->setPosition(CCPointZero);
		//m_pMenu->alignItemsVertically();
		//m_pMenu->setAnchorPoint(ccp(0, 0));
		//m_pMenu->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

		this->addChild(m_pMenu);
		this->setKeypadEnabled(true); //×¢²á·µ»Ø¼ü
		bRet = true;
	} while (0);
	return bRet;
}

void PopLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, kCCMenuHandlerPriority - 1, true);
	/*CCDirector::sharedDispatcher()->addTargetedDelegate(this,
		kCCMenuTouchPriority - 1, true);*/
}
void PopLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool PopLayer::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
	return true;
}
void PopLayer::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}
void PopLayer::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}
void PopLayer::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchCancelled(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}

void PopLayer::ReturnGame(CCObject * pSender)
{
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(m_MazeKey);
	this->removeFromParentAndCleanup(false);
}
void PopLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(m_MazeKey);
	this->removeFromParentAndCleanup(false);
}

void PopLayer::PauseMusic(CCObject * pSender)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("BackgroundStatus") || CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("BackgroundStatus", false);
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCUserDefault::sharedUserDefault()->setBoolForKey("EffectStatus", false);
		CCUserDefault::sharedUserDefault()->flush();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("BackgroundStatus", true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("EffectStatus", true);
		CCUserDefault::sharedUserDefault()->flush();
	}
}
void PopLayer::Exit(CCObject * pSender)
{
	//umeng::MobClickCpp::end();
	CCDirector::sharedDirector()->end();
}

void PopLayer::ReturnMain(CCObject * pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MainMenuScene::scene(), ccc3(255, 255, 255)));
}


void PopLayer::fun()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* background = CCSprite::create(CCString::createWithFormat("%s", str)->getCString());
	background->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	background->setScale(1.5f);
	this->addChild(background, 0);
}
void PopLayer::setMazeKey(CCKeypadDelegate * d)
{
	m_MazeKey = d;
}