#include "NGLayer.h"


bool NGLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCSprite * sprite = CCSprite::create("NGLayer.png");//背景要设成透明图层
		sprite->setPosition(ccp(origin.x + visibleSize.width*(1.0 / 2), origin.y + visibleSize.height*(2.0 / 3)));
		this->addChild(sprite);
		SimpleAudioEngine::sharedEngine()->playEffect("warning.wav");
		CCMenuItemImage * ExitBottom = CCMenuItemImage::create(
			"NGBottom1.png",
			"NGBottom2.png",
			this,
			menu_selector(NGLayer::Exit));

		ExitBottom->setPosition(ccp(origin.x + visibleSize.width*(5.0 / 7) - ExitBottom->getContentSize().width / 2+80
			, origin.y + visibleSize.height*(2.0 / 5) - ExitBottom->getContentSize().height / 2));

		m_pMenu = CCMenu::create(ExitBottom, NULL);

		m_pMenu->setPosition(CCPointZero);

		this->addChild(m_pMenu, 5);

		bRet = true;
	} while (0);
	return bRet;
}

void NGLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, kCCMenuHandlerPriority - 1, true);
	/*CCDirector::sharedDispatcher()->addTargetedDelegate(this,
	kCCMenuTouchPriority - 1, true);*/
}
void NGLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool NGLayer::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
	return true;
}
void NGLayer::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}
void NGLayer::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}
void NGLayer::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchCancelled(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}
void NGLayer::Exit(CCObject * pSender)
{
	this->removeFromParentAndCleanup(false);
}