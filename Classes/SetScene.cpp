#include "SetScene.h"



USING_NS_CC_EXT;
USING_NS_CC;
using namespace CocosDenshion;

CCScene * SetScene::scene()
{
	CCScene * scene = CCScene::create();

	SetScene * layer = SetScene::create();

	scene->addChild(layer);
	return scene;
}

bool SetScene::init()
{
	bool bRet = false;
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	do
	{
		// 背景音乐开关
		CCControlSwitch * switchControl = CCControlSwitch::create(
			CCSprite::create("switch-mask.png"),
			CCSprite::create("switch-on.png"),
			CCSprite::create("switch-off.png"),
			CCSprite::create("switch-thumb.png"),
			CCLabelTTF::create("On", "Arial-BoldMT", 16),
			CCLabelTTF::create("Off", "Arial-BoldMT", 16));
		switchControl->setPosition(ccp(origin.x + visibleSize.width*(2.0 / 3), origin.y + visibleSize.height*0.47));
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("BackgroundStatus"))
		{
			switchControl->setOn(true);
		}
		else
		{
			switchControl->setOn(false);
		}

		this->addChild(switchControl, 2);
		switchControl->addTargetWithActionForControlEvents(this,
			cccontrol_selector(SetScene::BackMC), CCControlEventValueChanged);

		//音效开关
		CCControlSwitch * switchControl2 = CCControlSwitch::create(
			CCSprite::create("switch-mask.png"),
			CCSprite::create("switch-on.png"),
			CCSprite::create("switch-off.png"),
			CCSprite::create("switch-thumb.png"),
			CCLabelTTF::create("On", "Arial-BoldMT", 16),
			CCLabelTTF::create("Off", "Arial-BoldMT", 16));
		switchControl2->setPosition(ccp(origin.x + visibleSize.width*(2.0 / 3), origin.y + visibleSize.height*0.17));
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
		{
			switchControl2->setOn(true);
		}
		else
		{
			switchControl2->setOn(false);
		}
		this->addChild(switchControl2, 2);
		switchControl2->addTargetWithActionForControlEvents(this,
			cccontrol_selector(SetScene::BackEC), CCControlEventValueChanged);

		CCSprite * spriteLogo = CCSprite::create("QLlogo.png");
		spriteLogo->setPosition(ccp(origin.x + visibleSize.width - spriteLogo->getContentSize().width / 2, origin.y + visibleSize.height*0.94));
		this->addChild(spriteLogo, 7);
		CCFadeOut * fadeOut = CCFadeOut::create(6.0f);
		CCRepeatForever * repeateForever1 = CCRepeatForever::create(fadeOut);
		spriteLogo->runAction(repeateForever1);

		//重新开始按钮
		CCMenuItemImage * RenewBottom = CCMenuItemImage::create(
			"ReturnN1.png",
			"ReturnN2.png",
			this,
			menu_selector(SetScene::RenewGame));
		RenewBottom->setPosition(ccp(origin.x + visibleSize.width - RenewBottom->getContentSize().width / 2,
			origin.y + RenewBottom->getContentSize().height / 2));

		//确认按钮
		CCMenuItemImage * ReturnBottom = CCMenuItemImage::create(
			"SetReturn1.png",
			"SetReturn2.png",
			this,
			menu_selector(InstructScene::ReturnMainMenu));
		ReturnBottom->setPosition(ccp(origin.x + visibleSize.width - ReturnBottom->getContentSize().width / 2,
			origin.y +visibleSize.height* 0.035+ ReturnBottom->getContentSize().height / 2+RenewBottom->getContentSize().height));

		CCMenu * pMenu = CCMenu::create(ReturnBottom,RenewBottom, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 2);

		CCSprite * Background = CCSprite::create("SetBackground.png");
		Background->setAnchorPoint(ccp(0, 0));
		this->addChild(Background, 1);


		CCMenuItemImage * spring = CCMenuItemImage::create(   //春天~ // 粒子系统
			"spring1.png", //换图片
			"spring2.png",
			this,
			menu_selector(MainMenuScene::Spring));
		spring->setPosition(ccp(origin.x + visibleSize.width*0.08, origin.y + visibleSize.height - spring->getContentSize().height / 2));
		//spring->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenuItemImage * summer = CCMenuItemImage::create(   //开始游戏
			"summer1.png", //换图片
			"summer2.png",
			this,
			menu_selector(MainMenuScene::Summer));
		summer->setPosition(ccp(origin.x + visibleSize.width*0.08,
			origin.y + visibleSize.height - spring->getContentSize().height / 2-summer->getContentSize().height * 1.5));
		//summer->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenuItemImage * full = CCMenuItemImage::create(   //开始游戏
			"full1.png", //换图片
			"full2.png",
			this,
			menu_selector(MainMenuScene::Full));
		full->setPosition(ccp(origin.x + visibleSize.width*0.08, origin.y + visibleSize.height - 
			spring->getContentSize().height - summer->getContentSize().height*1.5-full->getContentSize().height*1.5));
		//full->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenuItemImage * winter = CCMenuItemImage::create(   //开始游戏
			"winter1.png", //换图片
			"winter2.png",
			this,
			menu_selector(MainMenuScene::Winter));
		winter->setPosition(ccp(origin.x + visibleSize.width*0.08, origin.y + visibleSize.height -
			spring->getContentSize().height - summer->getContentSize().height*1.5- full->getContentSize().height*1.5-winter->getContentSize().height*1.5));
		//winter->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenu * pMenuA = CCMenu::create(spring, summer, full, winter, NULL);
		//pMenuA->alignItemsVertically();
		//pMenuA->setPosition(ccp(origin.x + visibleSize.width*0.08, origin.y + visibleSize.height*0.5));
		pMenuA->setPosition(CCPointZero);
		this->addChild(pMenuA, 3);

		bRet = true;
	} while (0);
	return bRet;
}

void SetScene::BackMC(CCObject* pSender, CCControlEvent event)
{
	CCControlSwitch * pSwitch = (CCControlSwitch *)pSender;
	if (pSwitch->isOn())
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("BackgroundStatus", true);
		CCUserDefault::sharedUserDefault()->flush();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("BackgroundStatus", false);
		CCUserDefault::sharedUserDefault()->flush();
	}
	
}

void SetScene::BackEC(CCObject * pSender, CCControlEvent event)
{
	CCControlSwitch * pSwitch = (CCControlSwitch *)pSender;
	if (pSwitch->isOn())
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("EffectStatus", true);
		CCUserDefault::sharedUserDefault()->flush();
		//SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCUserDefault::sharedUserDefault()->setBoolForKey("EffectStatus", false);
		CCUserDefault::sharedUserDefault()->flush();
	}
}

void SetScene::RenewGame(CCObject * pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, RenewScene::scene()));
}

void SetScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
}