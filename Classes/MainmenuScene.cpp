#include "MainmenuScene.h"
//CloseNormal    CloseSelected

CCScene * MainMenuScene::scene()
{
	CCScene * scene = CCScene::create(); 

	MainMenuScene * layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainMenuScene::init()
{
	bool bRet = false; 
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		particle = NULL;

		setKeypadEnabled(true);

		if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
		{
			CCUserDefault::sharedUserDefault()->setBoolForKey("BackgroundStatus", true);
			CCUserDefault::sharedUserDefault()->setBoolForKey("EffectStatus", true);
			CCUserDefault::sharedUserDefault()->flush();
		}
		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("BackGroundMusic.mp3");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BackGroundMusic.mp3", true);
			if (CCUserDefault::sharedUserDefault()->getBoolForKey("BackgroundStatus"))
			{

			}
			else
			{
				SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			}

		}
		
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		//CCSprite * Background = CCSprite::create("BackGround.jpg"); //更改图片
		CCSprite * Background = CCSprite::create("BackGround.png");
		//CCSprite * Background = CCSprite::create("BackGround1.png");
		Background->setAnchorPoint(ccp(0, 0));
		this->addChild(Background, 1);
		CCLayerColor * layerColor = CCLayerColor::create(ccc4(235, 240, 255,250));//ccc4(0, 0, 0, 0));背景图层
		this->addChild(layerColor, 0);

		CCSprite * spriteLogo = CCSprite::create("QLlogo.png");
		spriteLogo->setPosition(ccp(origin.x+visibleSize.width-spriteLogo->getContentSize().width/2, origin.y + visibleSize.height*0.94));
		this->addChild(spriteLogo,7);
		/*CCMoveTo * moveTo = CCMoveTo::create(4.0f, ccp(origin.x + visibleSize.width + spriteLogo->getContentSize().width,
			origin.y + visibleSize.height*0.94));
		CCRepeatForever * repeateForever = CCRepeatForever::create(moveTo);
		CCMoveTo * moveTo1 = CCMoveTo::create(4.0f, ccp(origin.x, origin.y + visibleSize.height*0.94));
		CCRepeatForever * repeateForever1 = CCRepeatForever::create(moveTo1);*/
		//CCFadeIn * fadeIn = CCFadeIn::create(4.0f);
		//CCRepeatForever * repeateForever = CCRepeatForever::create(fadeIn);
		//spriteLogo->runAction(repeateForever);
		CCFadeOut * fadeOut = CCFadeOut::create(6.0f);
		CCRepeatForever * repeateForever1 = CCRepeatForever::create(fadeOut);
		spriteLogo->runAction(repeateForever1);

		//CCSize size = CCEGLView::sharedOpenGLView()->getFrameSize();
		//CCSize size1 = CCDirector::sharedDirector()->FrameSize();
		CCMenuItemImage * StartMenu = CCMenuItemImage::create(   //开始游戏
			"StartMenu1.png", //换图片
			"StartMenu2.png",
			this,
			menu_selector(MainMenuScene::StartGame));
		StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width/2,
			origin.y+StartMenu->getContentSize().height/2));

		CCMenuItemImage * SetingMenu = CCMenuItemImage::create(
			"SetingMenu1.png", //换图片
			"SetingMenu2.png",
			this,
			menu_selector(MainMenuScene::SetM));

		SetingMenu->setPosition(ccp(origin.x + SetingMenu->getContentSize().width / 2,
			origin.y + visibleSize.height - SetingMenu->getContentSize().height / 2));

		CCMenuItemImage * InstructMenu = CCMenuItemImage::create(
			"InstructMenu1.png", //换图片
			"InstructMenu2.png",
			this,
			menu_selector(MainMenuScene::ReInstruct)); 
		InstructMenu->setPosition(ccp(origin.x + visibleSize.width * 0.001+InstructMenu->getContentSize().width / 2,
			origin.y + visibleSize.height - SetingMenu->getContentSize().height - InstructMenu->getContentSize().height / 2));

		CCMenuItemImage * ExitMenu = CCMenuItemImage::create(
			"back1.png", //换图片
			"back2.png",
			this,
			menu_selector(MainMenuScene::ExitM));
		/*ExitMenu->setPosition(ccp(origin.x + ExitMenu->getContentSize().width / 2,
			origin.y + visibleSize.height - SetingMenu->getContentSize().height - 
			InstructMenu->getContentSize().height - ExitMenu->getContentSize().height / 2));*/
		ExitMenu->setPosition(ccp(origin.x + ExitMenu->getContentSize().width / 3.2, 
			origin.y + ExitMenu->getContentSize().height * 3.0/ 2));

		CCMenuItemImage * spring = CCMenuItemImage::create(   //春天~
			"spring1.png", //换图片
			"spring12.png",
			this,
			menu_selector(MainMenuScene::Spring));
		//spring->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenuItemImage * summer = CCMenuItemImage::create(   //开始游戏
			"summer1.png", //换图片
			"summer2.png",
			this,
			menu_selector(MainMenuScene::Summer));
		//summer->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenuItemImage * full = CCMenuItemImage::create(   //开始游戏
			"full1.png", //换图片
			"full2.png",
			this,
			menu_selector(MainMenuScene::Full));
		//full->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
		origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenuItemImage * winter = CCMenuItemImage::create(   //开始游戏
			"winter1.png", //换图片
			"winter2.png",
			this,
			menu_selector(MainMenuScene::Winter));
		//winter->setPosition(CCPointZero);
		/*StartMenu->setPosition(ccp(origin.x + visibleSize.width - StartMenu->getContentSize().width / 2,
			origin.y + StartMenu->getContentSize().height / 2));*/
		CCMenu * pMenuA = CCMenu::create(spring, summer, full, winter, NULL);
		pMenuA->alignItemsHorizontally();
		pMenuA->setPosition(ccp(origin.x+visibleSize.width*0.4,origin.y+visibleSize.height*0.1));
		this->addChild(pMenuA, 3);
		CCMenu * pMenuStart = CCMenu::create(StartMenu,SetingMenu,InstructMenu, ExitMenu,NULL);
		pMenuStart->setPosition(CCPointZero);
		this->addChild(pMenuStart, 3);

		bRet = true;
	} while (0);
	return bRet;
}
void MainMenuScene::StartGame(CCObject * pSender)
{
	//CCUserDefault::sharedUserDefault()->setIntegerForKey("Count", 1);//这里先直接设置第一张图开始，其他的以后说。。。
	//CCUserDefault::sharedUserDefault()->flush();
	/*if (!CCUserDefault::sharedUserDefault()->getIntegerForKey("Count"))
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Count", 1);
		CCUserDefault::sharedUserDefault()->flush();
	}
	if (!CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxCount"))
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxCount", 1);
		CCUserDefault::sharedUserDefault()->flush();
	}
	if (!CCUserDefault::sharedUserDefault()->getIntegerForKey("IsFood"))
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("IsFood", 0);
		CCUserDefault::sharedUserDefault()->flush();
	}*/
	//////////////////////////////////////////////////////////////////////////
	//由于测试原因，先载入教程，以后再改。。
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))//存储文件不存在,头次开始加载游戏   
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Count", 1); //maze要载入的第几张地图
		CCUserDefault::sharedUserDefault()->flush();
		
		CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxCount", 1);//最多玩到第几张地图
		CCUserDefault::sharedUserDefault()->flush();

		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true); //初始化开始maze的坐标（春天）
		CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 48 + 24);
		CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 2400 - 24);
		CCUserDefault::sharedUserDefault()->flush();//提交
		
		for (int i = 0; i < 4; i++)  //初始化道具显示啥的
		{
			CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveS_%d", i)->getCString(), 1);
			CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("NPCS_%d", i+1)->getCString(), 0);
			CCUserDefault::sharedUserDefault()->flush();
		}
		for (int i = 0; i < 9; i++)  //初始化道具显示啥的
		{
			CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("NPCF_%d", i+1)->getCString(), 0);
			CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveF_%d", i)->getCString(), 1);
			CCUserDefault::sharedUserDefault()->flush();
		}
		
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, TeachScene::scene()));
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, MazeScene::create()));
	}
}

void MainMenuScene::ReInstruct(CCObject * pSender)				//说明按钮
{
	this->setKeypadEnabled(false);
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, InstructScene::scene()));
}

void MainMenuScene::ExitM(CCObject * pSender)					//退出按钮
{
	/*CCScene * EXIT = ExitScene::scene();
	CCDirector::sharedDirector()->replaceScene(EXIT);*/ //直接退出
	CCDirector::sharedDirector()->end();
}
void MainMenuScene::keyBackClicked()
{

	/*CCScene * EXIT = ExitScene::scene();
	CCDirector::sharedDirector()->replaceScene(EXIT);*/ //直接退出
	CCDirector::sharedDirector()->end();
}

void MainMenuScene::SetM(CCObject * pSender)				//设定按钮
{
	CCScene * EXIT = SetScene::scene();
	CCDirector::sharedDirector()->replaceScene(EXIT);
}

void MainMenuScene::Spring(CCObject * pSender)
{
	if (particle != NULL)
		this->removeChild(particle);
	particle =  CCParticleSnow::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("springflow.png"));
	this->addChild(particle, 7);
}
void MainMenuScene::Summer(CCObject * pSender)
{
	if (particle != NULL)
		this->removeChild(particle);
	particle = CCParticleRain::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("rain.png"));
	this->addChild(particle, 7);
}
void MainMenuScene::Full(CCObject * pSender)
{
	if (particle != NULL)
		this->removeChild(particle);
	particle = CCParticleSnow::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("fallleaves.png"));
	this->addChild(particle, 7);
}
void MainMenuScene::Winter(CCObject * pSsender)
{
	if (particle != NULL)
		this->removeChild(particle);
	particle = CCParticleSnow::create();
	this->addChild(particle, 7);
}