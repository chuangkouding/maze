#include "TeachScene.h"

int t;

CCScene * TeachScene::scene()
{
	CCScene * scene = CCScene::create();
	TeachScene * layer = TeachScene::create();
	scene->addChild(layer);
	return scene;
}
bool TeachScene::init()
{
	bool bRet = false;
	do
	{
		t = 0;
		//CC_BREAK_IF(!CCLayer::init);
		setKeypadEnabled(true);


		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLayerColor * layerColor = CCLayerColor::create(ccc4(224, 255, 255, 255));
		this->addChild(layerColor, 0);

		CCSprite  * BackGround = CCSprite::create("InstructBackGround.png");
		BackGround->setPosition(ccp(origin.x + visibleSize.width / 2,//- BackGround->getContentSize().width / 2,
			origin.y + visibleSize.height / 2)); // 2 //- BackGround->getContentSize().height / 2));
		this->addChild(BackGround, 1);

		CCSprite  * teach_start = CCSprite::create("teach_start.png"); //Î»ÖÃÒªµ÷
		teach_start->setPosition(ccp(origin.x + visibleSize.width / 2,//- BackGround->getContentSize().width / 2,
			origin.y + visibleSize.height / 2)); // 2 //- BackGround->getContentSize().height / 2));
		this->addChild(teach_start, 1);

		CCMenuItemImage * ReturnBottom = CCMenuItemImage::create(
			"ReturnButtom1.png",
			"ReturnButtom2.png",
			this,
			menu_selector(TeachScene::ReturnMainMenu));

		ReturnBottom->setPosition(ccp(origin.x + ReturnBottom->getContentSize().width*3 +150,
			origin.y /*+ visibleSize.height/2*/+ ReturnBottom->getContentSize().height/2  ));

		CCMenu * pMenu = CCMenu::create(ReturnBottom, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu,4);
		bRet = true;
	} while (0);
	return bRet;
}

void TeachScene::ReturnMainMenu(CCObject * sender)
{
	t++;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint  orign = CCDirector::sharedDirector()->getVisibleOrigin();
	if (t < 7)
	{
		CCSprite * sprite = CCSprite::create(CCString::createWithFormat("teach_%d.png", t)->getCString());
		//sprite->setPosition(ccp(orign.x, orign.y));
		sprite->setPosition(ccp(orign.x + visibleSize.width / 2, orign.y + visibleSize.height / 2));
		this->addChild(sprite, 3);
		CCScaleTo * scaleTo = CCScaleTo::create(0.1f, 0.1f, 0.1f);
		sprite->runAction(scaleTo);
		CCScaleTo * scaleTo1 = CCScaleTo::create(2.9f, 1.0f, 1.0f);
		sprite->runAction(scaleTo1);
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.8f, MazeScene::create()));
	}
}
void TeachScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
}