#include "CopyrightScene.h"
#include "MainmenuScene.h"

using namespace cocos2d;

CCScene* CopyrightScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		
		// 'layer' is an autorelease object
		CopyrightScene *layer = CopyrightScene::create();
		CC_BREAK_IF(! layer);
		
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CopyrightScene::init()
{
	bool bRet = false;
	do 
	{
		setKeypadEnabled(true);
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		//CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.

		this->scheduleOnce(schedule_selector(CopyrightScene::menuCloseCallback), 2.0f);

		/*CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"Continue1_1.png",
			"Continue1_2.png",
			this,
			menu_selector(CopyrightScene::menuCloseCallback));

		pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2
			, origin.y + visibleSize.height/2 + pCloseItem->getContentSize().height / 2));
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

		CCLabelTTF* pLabel = CCLabelTTF::create("  ", "arial", 24);
		CC_BREAK_IF(! pLabel);

		
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));

		this->addChild(pLabel, 1);*/

		// 3. Add add a splash screen, show the cocos2d splash image.
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pSprite = CCSprite::create("CopyrightScene.png");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to CopyrightScene layer as a child layer.
		this->addChild(pSprite, 0);

		bRet = true;
	} while (0);

	return bRet;
}

/*void CopyrightScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	//CCTransitionFade* transitionScene = CCTransitionFade::create(1.2f, MainMenuScene::scene());
//	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
//	CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MainMenuScene::scene(),ccc3(255,255,255)));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.2f, MainMenuScene::scene(), kCCTransitionOrientationLeftOver));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(1.2f, MainMenuScene::scene(), kCCTransitionOrientationDownOver));
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.2f, MainMenuScene::scene(),
			kCCTransitionOrientationDownOver));
	CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipX::create(1.2f, MainMenuScene::scene(),
		kCCTransitionOrientationDownOver));
	CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create(1.2f, MainMenuScene::scene(),
		kCCTransitionOrientationDownOver));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(1.2f, MainMenuScene::scene()));
	//////////////////////////////////////////////////////////////////////////
	
	//CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, MainMenuScene::scene()));//惊艳一下

	//CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1.2f, MainMenuScene::scene()));

	//CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.2f, MainMenuScene::scene()));
	//真正的淡入淡出。。。
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	//CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.2f, MainMenuScene::scene(),false));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFadeUp::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionProgressRadialCW::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionProgressVertical::create(1.2f, MainMenuScene::scene()));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionProgressInOut::create(1.2f, MainMenuScene::
}*/

void CopyrightScene::menuCloseCallback(float dt)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, MainMenuScene::scene(), ccc3(255, 255, 255)));
}

void CopyrightScene::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}