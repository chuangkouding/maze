#include "PositionController.h"

int dir[5][2] = { 1, 0, 0, 1, 0, -1, -1, 0,0,0 };

int ran[20][2] = {32,12,56,20,77,17,103,16,32,30,57,35,79,40,115,36,17,48,44,52,94,56,35,84,55,72,105,69,14,112,61,103,80,96,101,84,109,109,11,76};
int randd[20][2] = {33,12,57,20,77,18,104,16,32,31,57,36,80,40,114,36,18,48,45,52,95,56,36,84,56,72,105,70,15,112,61,102,81,96,101,83,109,110,12,76};
int ran1[50][2] = {74,46,64,86,42,74,18,106,91,42,103,3,11,38,34,50,67,14,114,36,91,121,67,59,111,64,91,17,50,115,7,78,23,58,50,60,24,122,2,3};
float foodS[4][2] = { 1, 1, 10, 5, 6, 77, 63, 40 };//吃的东西传送的
float foodSD[4][2] = { 35, 33, 56, 56, 32, 53, 44,11};//传送的位置
int duizhao[9] = { 1, 1, 2, 2, 2, 2, 3, 4, 5 };
float foodF[9][2] = { 72, 66, 77, 66, 62, 8, 86, 8, 47, 19, 62, 8, 1, 98, 15, 66, 65, 62 };
float foodFD[9][2] = { 70, 30, 6, 26, 40, 2, 2, 69, 6, 26, 91, 18, 34, 37, 34, 54, 34, 54 };
bool isAliveS[4];
bool isAliveF[9];
bool isFirst = 1;
int question1 = 1;
int direction = -1;
double jiansutime = 0;
double jiasutime = 0;
double fanxiangtime = 0;

bool PositionController::init()
{
	this->m_iXSpeed = this->m_iYSpeed = 0;//初始化速度为0

	this->setTouchEnabled(true); //设置允许触屏

	//this->schedule(schedule_selector(PositionController::update), 0.000001f);			//按秒执行update

	this->scheduleUpdate();//周期调用update
	//m_player->run(0);
	return true;
}


void PositionController::update(float dt)
{
	if (m_map == NULL || m_player == NULL)
		return;
	//减少相应buff时间
	if (jiasutime > 0)
	{
		jiasutime -= dt;
	}
	if (jiansutime > 0)
	{
		jiansutime -= dt;
	}
	if (fanxiangtime > 0)
	{
		fanxiangtime -= dt;
	}
	if (fabs(m_iXSpeed) < 1e-6 &&fabs( m_iYSpeed )< 1e-6)
	{
		m_player->stop();
		return;
	}
		
	

	CCPoint curPos = m_player->getPosition();
	CCPoint mapPosition = m_map->getPosition();
	CCSize mapTileSize = m_map->getMapSize();
	if (isFirst && CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			isAliveS[i] = CCUserDefault::sharedUserDefault()->getBoolForKey(CCString::createWithFormat("isAliveS_%d", i)->getCString());
			if (isAliveS[i] == 0)
			{
				CCTMXLayer * food = m_map->layerNamed("food");
				food->removeTileAt(ccp(float(foodS[i][0]), float(foodS[i][1])));
				food = m_map->layerNamed("meta");
				food->removeTileAt(ccp(float(foodS[i][0]), float(foodS[i][1])));
				break;
			}

		}
		isFirst = 0;
	}
	else if (isFirst && CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 3)
	{
		for (int i = 0; i < 9; i++)
		{
			isAliveS[i] = CCUserDefault::sharedUserDefault()->getBoolForKey(CCString::createWithFormat("isAliveF_%d", i)->getCString());
			if (isAliveF[i] == 0)
			{
				CCTMXLayer * food = m_map->layerNamed("food");
				food->removeTileAt(ccp(float(foodF[i][0]), float(foodF[i][1])));
				food = m_map->layerNamed("meta");
				food->removeTileAt(ccp(float(foodF[i][0]), float(foodF[i][1])));
				break;
			}

		}
		isFirst = 0;
	}
	float xSpeed, ySpeed;
	xSpeed = m_iXSpeed;
	ySpeed = m_iYSpeed;
	//buff速度改变
	if (jiasutime > 0)
	{
		xSpeed = m_iXSpeed * 2;
		ySpeed = m_iYSpeed * 2; //加速为2倍
	}
	else if (jiansutime > 0)
	{
		xSpeed = m_iXSpeed * 0.5;
		ySpeed = m_iYSpeed * 0.5; //减速为 原来的1/2
	}

	if (fanxiangtime > 0)
	{
		xSpeed = m_iXSpeed * -1;
		ySpeed = m_iYSpeed * -1;//方向反向
	}

	curPos.x += xSpeed;
	curPos.y += ySpeed;
	if (curPos.x < mapPosition.x+25)
		curPos.x = mapPosition.x+25;
	if (curPos.y < mapPosition.y+25)
		curPos.y = mapPosition.y+25;
	
	

	if (xSpeed > fabs(ySpeed))		//用direction变量判断是否转向，若转向，重置question1的标记变量使之可以被再次触发
	{
		m_player->run(1);
		if (direction != 1)
		{
			direction = 1;
			question1 = 1;
		}
	}
	else if (xSpeed  < -fabs(ySpeed))
	{
		m_player->run(3);
		if (direction != 3)
		{
			direction = 3;
			question1 = 1;
		}
	}
	else if (ySpeed > fabs(xSpeed))
	{
		m_player->run(0);
		if (direction != 0)
		{
			direction = 0;
			question1 = 1;
		}
	}
	else if (ySpeed< -fabs(xSpeed))
	{
		m_player->run(2);
		if (direction != 2)
		{
			direction = 2;
			question1 = 1;
		}
	}



	//在这里写碰撞检测
	CCPoint posOnMap = m_player->getPosition();
	CCSize playerSpriteSize = m_player->getSpriteSize();
	CCSize tiledSize = m_map->getTileSize();//单个格子的大小
	float x = curPos.x-mapPosition.x;
	float y = curPos.y-mapPosition.y;
	//CCLOG("%f %f", curPos.x, curPos.y);

	//////////////////////////////////////////////////////////////////////////坑
	bool fflag = 1;
	//CCLOG("$$$$$$");
	bool ok = 0;
	for (float i = curPos.x - playerSpriteSize.width / 4; i < curPos.x + playerSpriteSize.width / 4; i += tiledSize.width / 2)
	{
		for (float j = curPos.y - playerSpriteSize.height / 4; j <curPos.y + playerSpriteSize.height / 4; j += tiledSize.height / 2)
		{
			CCPoint tilePos = tileCoordForPosition(ccp(i,j));
			
			int tiledGid = meta->tileGIDAt(tilePos);
			if (tiledGid != 0)
			{
				CCPoint tiledPos = tileCoordForPosition(ccp(i,j));

				CCDictionary * propertiesDict = m_map->propertiesForGID(tiledGid);
				const CCString * prop = propertiesDict->valueForKey("trap");
				if (prop->m_sString.compare("true") == 0)
				{
					if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
					{
						SimpleAudioEngine::sharedEngine()->playEffect("trap.wav"); //掉入陷阱音效
					}
					
					CCScene * scene = DeadLayer::scene();
					CCDirector::sharedDirector()->replaceScene(scene);
					ok = 1;
				}
				prop = propertiesDict->valueForKey("jiansu"); //减速buff
				if (prop->m_sString.compare("true") == 0)
				{
					jiansutime = 5;
					jiasutime = -1;
					ok = 1;
				}
				prop = propertiesDict->valueForKey("jiasu"); //加速buff
				if (prop->m_sString.compare("true") == 0)
				{
					jiasutime = 5;
					jiansutime = -1;
					ok = 1;
				}
				prop = propertiesDict->valueForKey("fanxiang"); //反向buff
				if (prop->m_sString.compare("true") == 0)
				{
					fanxiangtime = 5;
					ok = 1;
				}
				
				prop = propertiesDict->valueForKey("food");  //“食物”
				if (prop->m_sString.compare("true") == 0)
				{
					if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 1)
					{
						for (int k = 0; k < 4; k++)
						{
							if (fabs(tiledPos.x - foodS[k][0]) < 10e-3 && fabs(tiledPos.y - foodS[k][1]) < 10e-3)
							{
								bool isTouch = CCUserDefault::sharedUserDefault()->getBoolForKey(CCString::createWithFormat("NPCS_%d", k+1)->getCString());
								if (isTouch)
								{
									//CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("NPCS_%d", k + 1)->getCString(),0);
									if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
									{
										SimpleAudioEngine::sharedEngine()->playEffect("food.wav"); //吃到东西音效
									}
									
									CCTMXLayer * food = m_map->layerNamed("food");
									food->removeTileAt(tiledPos);
									food = m_map->layerNamed("meta");
									food->removeTileAt(tiledPos);
									curPos.x = foodSD[k][0] * tiledSize.width;
									curPos.y = (mapTileSize.height - foodSD[k][1])*tiledSize.height;
									CCLOG("%f   %f", mapTileSize.width, mapTileSize.height - foodSD[k][0]);
									CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveS_%d", k)->getCString(),0);
									break;
								}
								ok = 1;
							}
						}
					}
					else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 3)
					{
						for (int k = 0; k < 9; k++)
						{
							if (fabs(tiledPos.x - foodF[k][0]) < 10e-3 && fabs(tiledPos.y - foodF[k][1]) < 10e-3)
							{
								bool isTouch = CCUserDefault::sharedUserDefault()->getBoolForKey(CCString::createWithFormat("NPCF_%d", duizhao[k])->getCString());
								if (isTouch)
								{
									//CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("NPCF_%d", duizhao[k])->getCString(),0);
									if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
									{
										SimpleAudioEngine::sharedEngine()->playEffect("food.wav"); //吃到东西音效
									}
									CCTMXLayer * food = m_map->layerNamed("food");
									food->removeTileAt(tiledPos);
									food = m_map->layerNamed("meta");
									food->removeTileAt(tiledPos);
									curPos.x = foodFD[k][0] * tiledSize.width;
									curPos.y = (mapTileSize.height - foodFD[k][1])*tiledSize.height;
									CCUserDefault::sharedUserDefault()->setBoolForKey(CCString::createWithFormat("isAliveF_%d", k)->getCString(), 0);
									break;
								}
								ok = 1;
							}
						}
					}
					
				}
				int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("Count");
				prop = propertiesDict->valueForKey("win");
				if (prop->m_sString.compare("true") == 0)
				{
					if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
					{
						SimpleAudioEngine::sharedEngine()->playEffect("win.mp3");//胜利音效
					}
					int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("Count");
					if (count < 4)
					{
						CCScene * pScene = NextMaze::scene();
						CCDirector::sharedDirector()->replaceScene(pScene);
					}
					else
					{
						CCScene * pScene = FinalScene::scene();
						CCDirector::sharedDirector()->replaceScene(pScene);
					}
					ok = 1;
				}
				
				prop = propertiesDict->valueForKey("rand"); //传送门音效
				if (prop->m_sString.compare("true") == 0)
				{
					ok = 1;
					for (int l = 0; l < 20; l++)
					{
						if (((fabs(ran[l][0] - tilePos.x) < 10e-3 && fabs(ran[l][1] - tilePos.y) < 10e-3)) || ((fabs(randd[l][0] - tilePos.x) < 10e-3 && fabs(randd[l][1] - tilePos.y) < 10e-3)))
						{
							if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
							{
								SimpleAudioEngine::sharedEngine()->playEffect("rand.wav");
							}
							
							curPos.x = (ran1[l][0]) * tiledSize.width;
							curPos.y = (mapTileSize.height - ran1[l][1]) * tiledSize.height;
							break;
							ok = 1;
						}
					}
				}
			}
			if (ok)
				break;
		}
		if (ok)
		{
			ok = 0;
			break;
		}
	}

	if (fabs(xSpeed) > 1e-3)//正在左右移动
	{
		int temp = xSpeed > 0 ? 1 : -1;
		int flag = 0;
		CCPoint dstPos = CCPoint(x + temp*playerSpriteSize.width/2, y); //右方中心坐标点
		int ffflag = 0;
		for (float i = y - playerSpriteSize.height / 2; !ffflag || i <= y + playerSpriteSize.height / 2; i += tiledSize.height / 2)
		{
			if (i > y + playerSpriteSize.height / 2)
			{
				i = y + playerSpriteSize.height / 2;
				ffflag = 1;
			}
			float ni = i;
			if (i < y)
			{
				ni += 1;
			}
			if (i > y)
			{
				ni -= 1;
			}
				
			CCPoint tiledPos = tileCoordForPosition(ccp(dstPos.x, ni - ySpeed));
			int tiledGid = meta->tileGIDAt(tiledPos);

			if (tiledGid != 0)
			{
				CCDictionary * propertiesDict = m_map->propertiesForGID(tiledGid);
				const CCString* prop = propertiesDict->valueForKey("Collidable");

				if (prop->m_sString.compare("true") == 0)
				{
					flag = 1;
				}
				if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 1)//如果地图是春天
				{
					display(question1, propertiesDict, prop, "Question", "springLQ_1.png");
					display(question1, propertiesDict, prop, "question2", "springAQ_3.png");
					display(question1, propertiesDict, prop, "question3", "springAQ_5.png");
					display(question1, propertiesDict, prop, "question4", "springAQ_7.png");
					display(question1, propertiesDict, prop, "question5", "springAQ_9.png");
					display(question1, propertiesDict, prop, "question6", "springAQ_10.png");
					display(question1, propertiesDict, prop, "question7", "springAQ_11.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_1", "springAQ_2.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_2", "springAQ_4.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_3", "springAQ_6.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_4", "springAQ_8.png");
				}
				else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 2)//夏天
				{
					display(question1, propertiesDict, prop, "question1", "summer_1.png");
					display(question1, propertiesDict, prop, "question2", "summer_2.png");
					display(question1, propertiesDict, prop, "question3", "summer_3.png");
					display(question1, propertiesDict, prop, "question4", "summer_4.png");
					display(question1, propertiesDict, prop, "question5", "summer_5.png");
					display(question1, propertiesDict, prop, "question6", "summer_6.png");
					display(question1, propertiesDict, prop, "question7", "summer_7.png");
					display(question1, propertiesDict, prop, "question8", "summer_8.png");
					display(question1, propertiesDict, prop, "question9", "summer_9.png");
					display(question1, propertiesDict, prop, "question10", "summer_10.png");

				}
				else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 3)//秋天
				{
					display(question1, propertiesDict, prop, "question1", "fall_1.png");
					display(question1, propertiesDict, prop, "question2", "fall_2.png");
					display(question1, propertiesDict, prop, "question3", "fall_3.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_1", "fall_4.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_2", "fall_5.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_3", "fall_6.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_4", "fall_7.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_5", "fall_8.png");

				}
				else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 4)//冬天
				{
					display(question1, propertiesDict, prop, "question", "winter_1.png");
				}
			}
		}
		if (flag)
		{
			curPos.x -= xSpeed;
		}
			
	}
	if (fabs(ySpeed) > 1e-3)		//正在上下移动
	{
		int temp = ySpeed > 0 ? 1 : -1;
		int flag = 0;
		CCPoint dstPos = CCPoint(x, y + temp*playerSpriteSize.height / 2); //右方中心坐标点
		int ffflag = 0;
		for (float i = x - playerSpriteSize.width / 2; !ffflag||i <= x + playerSpriteSize.width / 2; i += tiledSize.width / 2)
		{
			if (i > x + playerSpriteSize.width / 2)
			{
				i = x + playerSpriteSize.width / 2;
				ffflag = 1;
			}
			float ni = i;
			if (i < x)
			{
				ni += 1;
			}
			if (i > x)
				ni -= 1;
			CCPoint tiledPos = tileCoordForPosition(ccp(ni-xSpeed, dstPos.y));
			int tiledGid = meta->tileGIDAt(tiledPos);

			if (tiledGid != 0)
			{
				CCDictionary * propertiesDict = m_map->propertiesForGID(tiledGid);
				const CCString* prop = propertiesDict->valueForKey("Collidable");

				if (prop->m_sString.compare("true") == 0)
				{
					flag = 1;
				}
				if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 1)//如果地图是春天
				{
					display(question1, propertiesDict, prop, "Question", "springUQ_1.png");
					display(question1, propertiesDict, prop, "question2", "springAQ_3.png");
					display(question1, propertiesDict, prop, "question3", "springAQ_5.png");
					display(question1, propertiesDict, prop, "question4", "springAQ_7.png");
					display(question1, propertiesDict, prop, "question5", "springAQ_9.png");
					display(question1, propertiesDict, prop, "question6", "springAQ_10.png");
					display(question1, propertiesDict, prop, "question7", "springAQ_11.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_1", "springAQ_2.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_2", "springAQ_4.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_3", "springAQ_6.png");
					display_NPC(question1, propertiesDict, prop, "NPCS_4", "springAQ_8.png");

				}
				else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 2)//夏天
				{
					display(question1, propertiesDict, prop, "question1", "summer_1.png");
					display(question1, propertiesDict, prop, "question2", "summer_2.png");
					display(question1, propertiesDict, prop, "question3", "summer_3.png");
					display(question1, propertiesDict, prop, "question4", "summer_4.png");
					display(question1, propertiesDict, prop, "question5", "summer_5.png");
					display(question1, propertiesDict, prop, "question6", "summer_6.png");
					display(question1, propertiesDict, prop, "question7", "summer_7.png");
					display(question1, propertiesDict, prop, "question8", "summer_8.png");
					display(question1, propertiesDict, prop, "question9", "summer_9.png");
					display(question1, propertiesDict, prop, "question10", "summer_10.png");

				}
				else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 3)//秋天
				{
					display(question1, propertiesDict, prop, "question1", "fall_1.png");
					display(question1, propertiesDict, prop, "question2", "fall_2.png");
					display(question1, propertiesDict, prop, "question3", "fall_3.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_1", "fall_4.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_2", "fall_5.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_3", "fall_6.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_4", "fall_7.png");
					display_NPC(question1, propertiesDict, prop, "NPCF_5", "fall_8.png");
				}
				else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Count") == 4)//冬天
				{
					display(question1, propertiesDict, prop, "question", "winter_1.png");
				}

			}
		}
		if (flag)
			curPos.y -= ySpeed;
	}
	m_player->setPosition(ccp(curPos.x, curPos.y));
	setViewPointByPlayer();

	//setPlayerPositionOnMap(ccp(curPos.x, ));
}
CCPoint PositionController::tileCoordForPosition(CCPoint pos)
{
	CCSize mapTiledNum = m_map->getMapSize();
	CCSize tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height*tiledSize.height - pos.y) / tiledSize.height;
	
	return ccp(x, y);
}
void PositionController::setViewPointByPlayer() //镜头和小人一起运动
{
	if (m_player == NULL || m_map == NULL)
	{
		return;
	}

	CCLayer* parent = (CCLayer*)getParent();
	CCSize mapTiledNum = m_map->getMapSize();
	CCSize tiledSize = m_map->getTileSize();
	CCSize mapSize = CCSize(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint spritePos = m_player->getPosition();
	float x = fmax(spritePos.x, visibleSize.width / 2);
	float y = fmax(spritePos.y, visibleSize.height / 2);
	CCPoint mapPos = m_map->getPosition();
	x = fmin(x, mapPos.x+mapSize.width - visibleSize.width / 2);
	y = fmin(y, mapPos.y+mapSize.height - visibleSize.height / 2);
	CCPoint destPos = CCPoint(x, y);
	CCPoint centerPos = CCPoint(visibleSize.width / 2, visibleSize.height / 2);
	CCPoint viewPos = ccpSub(centerPos, destPos);
	
	parent->setPosition(viewPos);
}

CCPoint PositionController::getPlayerPositionOnMap()
{
	return   m_player->getPosition() + m_map->getPosition();
}
void PositionController::setListenMap(CCTMXTiledMap *map)
{
	CC_SAFE_RETAIN(map);
	this->m_map = map;

	this->meta = m_map->layerNamed("meta");
	this->meta->setVisible(false);
	this->meta->retain();
}

void PositionController::setListenPlayer(Player *player)
{
	m_player = player;
}

void PositionController::setiXSpeed(float iSpeed)
{
	m_iXSpeed = iSpeed;
}
void PositionController::setiYSpeed(float iSpeed)
{
	m_iYSpeed = iSpeed;
}

CCPoint startTouchLocation;
bool PositionController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//获得起始touch 的坐标
	startTouchLocation = pTouch->getLocationInView();
	startTouchLocation = CCDirector::sharedDirector()->convertToGL(startTouchLocation);
	m_rocker_bg->setPosition(startTouchLocation);
	m_rocker_bg->setVisible(true);
	m_rocker->setPosition(startTouchLocation);
	m_rocker->setVisible(true);
	return true;
}
void PositionController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//获得当前touch坐标
	CCPoint pos = pTouch->getLocationInView();
	pos = CCDirector::sharedDirector()->convertToGL(pos);
	float dx = pos.x - startTouchLocation.x;
	float dy = pos.y - startTouchLocation.y;
	float posDis = sqrt(dx*dx + dy*dy);
	if (posDis > 100)
	{
		m_rocker->setPosition(CCPoint(startTouchLocation.x + dx * 100 / posDis, startTouchLocation.y + dy * 100 / posDis));
	}
	else
	{
		m_rocker->setPosition(pos);
	}
	if (fabs(dx) < 10)dx = 0;
	if (fabs(dy) < 10)dy = 0;
	double dd = 1;
	if (!(dx == 0 && dy == 0))
		 dd = sqrt(dx*dx + dy*dy);
	//CCLOG("%d %f %f", m_PlayerMaxSpeed, dx, dd);
	//CCLOG("%f %f", m_PlayerMaxSpeed*dx / dd, m_PlayerMaxSpeed*dy / dd);


	
	setiXSpeed(m_PlayerMaxSpeed*dx / dd);
	setiYSpeed(m_PlayerMaxSpeed*dy / dd);
}

void PositionController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	setiXSpeed(0);
	setiYSpeed(0);
	m_player->stop();
	m_rocker_bg->setVisible(false);
	m_rocker->setVisible(false);
}
void PositionController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	setiXSpeed(0);
	setiYSpeed(0);
	m_player->stop();
	m_rocker_bg->setVisible(false);
	m_rocker->setVisible(false);
	m_mazeSceneKeypad->keyBackClicked();
}
void PositionController::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PositionController::setRocker_bg(CCSprite *rocker_bg)
{
	m_rocker_bg = rocker_bg;
}
void PositionController::setRocker(CCSprite *rocker)
{
	m_rocker = rocker;
}
void PositionController::setMazeSceneKeypad(CCKeypadDelegate *mazeSceneKeypad)
{
	m_mazeSceneKeypad = mazeSceneKeypad;
}
void PositionController::setMenuLayer(CCLayer *menuLayer)
{
	m_menuLayer = menuLayer;
	
}

void PositionController::display(int &question1, CCDictionary * propertiesDict,const CCString* prop,string str,const char * str2)//参数说明：第一个是用于防止碰撞一次弹出多个对话框，第二和第三作用不明，但一定要带，第4个是图块的属性，第5个是弹出的对话框的图片名字
{
	prop = propertiesDict->valueForKey(str);		//对话框的实现
	if (prop->m_sString.compare("true") == 0)
	{
		if (question1 == 1)								//如果这个标记变量=1，说明未被触发过，可以触发
		{
			PopupLayer * question = PopupLayer::create();
			if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
			{
				SimpleAudioEngine::sharedEngine()->playEffect("Effect_miao.wav"); //猫叫音效
			}
			
			strcpy(question->picture,str2);		//传参
			question->fun();					//调用fun函数将图片显示
			m_menuLayer->addChild(question);
			this->setTouchEnabled(false);						//强制中断触摸事件
			setiXSpeed(0);										//让主角停下来
			setiYSpeed(0);
			m_rocker_bg->setVisible(false);						//让摇杆消失
			m_rocker->setVisible(false);
			this->setTouchEnabled(true);						//重新启动触摸事件
			question1 = 0;							//标记变量变成0避免被多次触发
		}
	}
}
void PositionController::display_NPC(int &question1, CCDictionary * propertiesDict, const CCString* prop, const char * str, const char * str2)
{
	prop = propertiesDict->valueForKey(str);		//对话框的实现
	if (prop->m_sString.compare("true") == 0)
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(str, true);
		CCUserDefault::sharedUserDefault()->flush();
		if (question1 == 1)								//如果这个标记变量=1，说明未被触发过，可以触发
		{
			PopupLayer * question = PopupLayer::create();
			if (CCUserDefault::sharedUserDefault()->getBoolForKey("EffectStatus"))
			{
				SimpleAudioEngine::sharedEngine()->playEffect("Effect_miao.wav"); //猫叫音效
			}
			strcpy(question->picture, str2);		//传参
			question->fun();					//调用fun函数将图片显示
			m_menuLayer->addChild(question);
			this->setTouchEnabled(false);						//强制中断触摸事件
			setiXSpeed(0);										//让主角停下来
			setiYSpeed(0);
			m_rocker_bg->setVisible(false);						//让摇杆消失
			m_rocker->setVisible(false);
			this->setTouchEnabled(true);						//重新启动触摸事件
			question1 = 0;							//标记变量变成0避免被多次触发
		}
	}
}