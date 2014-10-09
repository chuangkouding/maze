#include "final2_1.h"

CCScene* final2_1::scene() {
	CCScene* scene = CCScene::create();

	final2_1* layer = final2_1::create();

	scene->addChild(layer);

	return scene;
}

bool final2_1::init() {
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCUserDefault::sharedUserDefault()->setIntegerForKey("Count", 1);
	CCUserDefault::sharedUserDefault()->flush();//1111
	CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 48 + 24);//春天初始位置
	CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 2400 - 24);
	CCUserDefault::sharedUserDefault()->flush();
	for (int i = 0; i < 4; i++)  //初始化道具显示啥的
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveS_%d", i)->getCString(), 1);
		CCUserDefault::sharedUserDefault()->flush();
	}


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"closeall.png",
		"closeall2.png",
		this,
		menu_selector(final2_1::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));
	CCMenuItemImage *pRestart = CCMenuItemImage::create(
		"restart.png", //png.jpg等图片格式都是可以的////////////
	"restart2.png",
		this,
		menu_selector(final2_1::menuCallback));
	//CC_BREAK_IF(! pCloseItem);
	pRestart->setPosition(ccp(origin.x+visibleSize.width-pCloseItem->getContentSize().width/2-120/*::sharedDirector()->getWinSize().width - 70*/, 94));

	CCMenu* pMenu = CCMenu::create(pCloseItem,pRestart, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	//最后添加进去，就创建成功了
	/////////////////////////////
	CCLabelTTF* pLabel = CCLabelTTF::create("   ", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("thelast.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	return true;

	//CCLabelTTF* label = CCLabelTTF::create("hi?", "Arial", 20);
	//label->setPosition(ccp(200, 200));
//
	//CCSprite* sprite = CCSprite::create("closeall.png");
	//sprite->setPosition(ccp(300, 300));
	//this->addChild(sprite);
	//this->addChild(label);

}
void final2_1::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
void final2_1::menuCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, MainMenuScene::scene()));
}



