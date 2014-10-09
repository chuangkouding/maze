#include "PopLayer.h"


bool PopupLayer::init()
{

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 155)));

		setKeypadEnabled(true);
		bRet = true;
	} while (0);
	return bRet;
}

void PopupLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, kCCMenuHandlerPriority - 1, true);
	/*CCDirector::sharedDispatcher()->addTargetedDelegate(this,
	kCCMenuTouchPriority - 1, true);*/
}
void PopupLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool PopupLayer::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
	return true;
}
void PopupLayer::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}
void PopupLayer::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}
void PopupLayer::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchCancelled(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}

void PopupLayer::keyBackClicked()
{
	this->removeFromParentAndCleanup(false);
}

void PopupLayer::Confirm(CCObject * pSender)
{
	this->removeFromParentAndCleanup(false);
}

void PopupLayer::fun()
{
	//CCLOG(picture);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* background = CCSprite::create(CCString::createWithFormat("%s", picture)->getCString());
	background->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	//background->setScale(1.5f);
	this->addChild(background, 0);
	CCMenuItemImage * ReturnGBottom = CCMenuItemImage::create(
		"pop_button.png",
		"pop_button.png",
		this,
		menu_selector(PopupLayer::Confirm));


	m_pMenu = CCMenu::create(ReturnGBottom, NULL);
	m_pMenu->alignItemsVertically();

	m_pMenu->setAnchorPoint(ccp(0, 0));
	m_pMenu->setPosition(ccp(visibleSize.width / 2+120,+ visibleSize.height / 2-55));
	this->addChild(m_pMenu,1);
	setTouchEnabled(true);
	this->setKeypadEnabled(true); //×¢²á·µ»Ø¼ü
}