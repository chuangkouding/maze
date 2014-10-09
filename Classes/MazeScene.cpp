#include "MazeScene.h"

MazeScene::MazeScene()
{

}
bool MazeScene::init()
{
	isHaveSaveFile();
	double x, y;
	x = CCUserDefault::sharedUserDefault()->getDoubleForKey("xlabel");
	y = CCUserDefault::sharedUserDefault()->getDoubleForKey("ylabel");
	//m_SoundStatus = true;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BackGroundMusic.mp3", true);

	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);

	//两个层 控制菜单层，放置菜单、控制按钮   一个地图层 放置地图、主角、控制器 两个层相互不影响

	//加载地图层
	CCLayer * mapLayer = CCLayer::create();

	int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("Count");
	//CCLOG("####　　%d", count);
	//CCLOG("$####@@$@$   %lf %lf", x, y);
	//CCTMXTiledMap *map = CCTMXTiledMap::create("Maze.tmx");
	CCTMXTiledMap *map = NULL;
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
	if (count == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("spring.mp3");  //音乐要换
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("spring.mp3", true);
		map = CCTMXTiledMap::create("48.tmx");
	}
	else if (count == 2)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("summer.mp3");  //音乐要换
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("summer.mp3", true);
		map = CCTMXTiledMap::create("summer.tmx");
	}
	else if (count == 3)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("fall.mp3");  //音乐要换
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("fall.mp3", true);
		map = CCTMXTiledMap::create("fall.tmx");
	}
	else if (count == 4)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("winter.mp3");  //音乐要换
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("winter.mp3", true);
		map = CCTMXTiledMap::create("winter.tmx");
	}
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("BackgroundStatus"))
	{

	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	//CCTMXTiledMap *map = CCTMXTiledMap::create("Maze.tmx");
	//CCTMXTiledMap *map = CCTMXTiledMap::create("48.tmx");
	m_map = map;
	m_map->setPosition(ccp(0, 0));
	mapLayer->addChild(m_map);
	this->addChild(mapLayer);
	
	//生成主角
	CCSprite* playerSprite = CCSprite::create("Player_first.png");
	// 将精灵绑定到主角对象上 
	Player *mPlayer = Player::create();
	MazeScene::m_Player = mPlayer;
	m_Player->bindSprite(playerSprite);
	m_Player->run(1);
	m_Player->stop();
	mapLayer->addChild(m_Player);
	//this->addChild(playerLayer);
//	mPlayer->setPosition(50, 50);
	m_Player->setPosition(x, y);
	float xx = m_Player->getPositionX();
	float yy = m_Player->getPositionY();
	
	CCSprite *rocker_bg = CCSprite::create("Rocker_bg.png");		//摇杆背景
	CCSprite *rocker = CCSprite::create("Rocker_bf.png");			//摇杆前面的小球
	rocker->setVisible(false);
	rocker_bg->setVisible(false);

	//加载位置控制器
	PositionController * positionController = PositionController::create();
	positionController->setListenMap(m_map);
	positionController->setListenPlayer(m_Player);
	positionController->setRocker(rocker);
	positionController->setRocker_bg(rocker_bg);
	positionController->setMazeSceneKeypad(this);
	
	mapLayer->addChild(positionController);

	// 以下为 菜单、按钮控制层
	CCLayer * menuLayer = CCLayer::create();
	menuLayer->addChild(rocker_bg);
	menuLayer->addChild(rocker);
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//退出按钮
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"GSet1.png",
		"GSet2.png",
		this,
		menu_selector(MazeScene::menuSoundSettingCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
		origin.y + visibleSize.height - pCloseItem->getContentSize().height / 2));

	/*CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
		"ReturnM1.png",
		"ReturnM2.png",
		this,
		menu_selector(InstructScene::ReturnMainMenu));

	pCloseItem2->setPosition(ccp(origin.x + visibleSize.width - pCloseItem2->getContentSize().width / 2,
		origin.y + visibleSize.height - pCloseItem2->getContentSize().height / 2));*/

	// create menu, it's an autorelease object

	////////===

	//CCMenu* pMenu = CCMenu::create(pCloseItem, pCloseItem2, NULL);
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	menuLayer->addChild(pMenu, 1);
	this->addChild(menuLayer);
	positionController->setMenuLayer(menuLayer);
	positionController->setViewPointByPlayer(); //初始一下镜头位置
	
	//mPlayer->runAction(createAnimate());;
	return true;
}

void MazeScene::menuSoundSettingCallback(CCObject* pSender)					//关闭开启声音
{
	//GlobalSetting::setSoundStatus(!GlobalSetting::getSoundStatus());
	keyBackClicked();
}

/*void MazeScene::ReturnMainMenu(CCObject * sender)					//返回主菜单
{
	CCScene * main = MainMenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(main);
}*/

bool MazeScene::isHaveSaveFile()			//检查是否有存档
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))//存储文件不存在,头次开始加载游戏   
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", 48+24);
		CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", 2400-24);
		CCUserDefault::sharedUserDefault()->flush();			//提交 
		return false;
	}
	else
	{        //        CCLog("存储文件已存在");        
		return true;
	}
}
void MazeScene::keyBackClicked()
{
	CCPoint pos = m_Player->getPosition();
	CCUserDefault::sharedUserDefault()->setDoubleForKey("xlabel", pos.x);			//存x轴y轴坐标
	CCUserDefault::sharedUserDefault()->setDoubleForKey("ylabel", pos.y);
	CCUserDefault::sharedUserDefault()->flush();
	//提交
	CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
	PopLayer * poplayer = PopLayer::create();
	poplayer->setMazeKey(this);
	
	this->addChild(poplayer);
	
}