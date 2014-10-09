#include "InstructScene.h"


CCScene * InstructScene::scene()
{
	CCScene * scene = CCScene::create();
	InstructScene * layer = InstructScene::create();
	scene->addChild(layer);
	return scene;
}
bool InstructScene::init()
{
	bool bRet = false;
	do 
	{
		//CC_BREAK_IF(!CCLayer::init);
		setKeypadEnabled(true);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLayerColor * layerColor = CCLayerColor::create(ccc4(224, 255, 255, 255));
		this->addChild(layerColor,0);

		CCSprite  * BackGround = CCSprite::create("InstructBackGround.png");
		BackGround->setPosition(ccp(origin.x + visibleSize.width / 2 ,//- BackGround->getContentSize().width / 2,
			origin.y + visibleSize.height/2)); // 2 //- BackGround->getContentSize().height / 2));
		this->addChild(BackGround, 1);

		CCSprite * spriteLogo = CCSprite::create("QLlogo.png");
		spriteLogo->setPosition(ccp(origin.x + visibleSize.width - spriteLogo->getContentSize().width / 2, origin.y + visibleSize.height*0.94));
		this->addChild(spriteLogo, 7);
		CCFadeOut * fadeOut = CCFadeOut::create(6.0f);
		CCRepeatForever * repeateForever1 = CCRepeatForever::create(fadeOut);
		spriteLogo->runAction(repeateForever1);

		CCMenuItemImage * ReturnBottom = CCMenuItemImage::create(
			"ReturnButtom11.png",
			"ReturnButtom12.png", 
			this,
			menu_selector(InstructScene::ReturnMainMenu));

		ReturnBottom->setPosition(ccp(origin.x + ReturnBottom->getContentSize().width / 2,
			origin.y+visibleSize.height-ReturnBottom->getContentSize().height / 2));

		CCMenu * pMenu = CCMenu::create(ReturnBottom, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 2);
		bRet = true;
	} while (0);
	return bRet;
}

void InstructScene::ReturnMainMenu(CCObject * sender)
{
	CCScene * main = MainMenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(main);
}
void InstructScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
}