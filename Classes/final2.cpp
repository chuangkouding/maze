#include "final2.h"


USING_NS_CC;

CCScene* FinalScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FinalScene *layer = FinalScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FinalScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("BackgroundStatus"))
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("final.mp3", true);
	}
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(FinalScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    
    CCLabelTTF* pLabel = CCLabelTTF::create("   ", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "FinalScene" splash screen"
    CCSprite* pSprite = CCSprite::create("FinalScene.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("final.mp3", true);
    
    return true;
}

void FinalScene::menuCloseCallback(CCObject* pSender) 
{
	// "close" menu item clicked
	//CCDirector::sharedDirector()->end();

	// 切换场景
	//CCDirector::sharedDirector()->replaceScene(final2_1::scene());

	// 包含特效的场景切换
	//CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(3.0f, final2_1::scene()));
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, final2_1::scene()));
}

void FinalScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, final2_1::scene()));
}
