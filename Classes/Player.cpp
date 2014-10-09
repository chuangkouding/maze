#include "Player.h"


bool Player::init()
{
	m_direction = 1;
	m_isRunning = true;
	//初始化主角动画
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_frameCache->addSpriteFramesWithFile("Player.plist", "Player.png"); //主角跑动图片加载
	m_frameCache->retain();
	

	for (int i = 0; i < 4; i++)
	{
		
		CCSpriteFrame * frame = NULL;
		CCArray *frameList = CCArray::create();
		//创建精灵帧对象，添加到列表里
		for (int j = 0; j < 4; j++)
		{
			frame = m_frameCache->spriteFrameByName(CCString::createWithFormat("Player_%d_%d.png", i, j)->getCString());
			frameList->addObject(frame);
		}
		
		//根据精灵帧对象创建动画对象

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameList);
		animation->setLoops(-1); //循环次数 -1为无限循环
		animation->setDelayPerUnit(0.2f);//每一帧播放的间隔

		//创建动画动作
		m_animate[i] = CCAnimate::create(animation);
		m_animate[i]->retain();

	}

	
	
	return true;
}
void Player::bindSprite(CCSprite * Sprite)
{
	m_sprite = Sprite;
	this->addChild(m_sprite);
}

CCSize Player::getSpriteSize()
{
	return m_sprite->getContentSize();
}
void Player::run(int x)
{
	//x = 1;
	
	if (m_direction==x && m_isRunning)
	{
		return;
	}
	m_isRunning = true;
	m_direction = x;
	CCLOG("%d", x);
	m_sprite->stopAllActions();	
	
	//精灵执行动作
	m_sprite->runAction(m_animate[x]);
}
Player::~Player()
{
	for (int i = 0; i < 4; i++)
	{
		m_animate[i]->release();
	}
	m_frameCache->release();
}
void Player::stop()
{
	if (!m_isRunning)return;
	m_isRunning = false;
	m_sprite->stopAllActions();
	m_sprite->createWithSpriteFrame(m_frameCache->spriteFrameByName(CCString::createWithFormat("Player_%d_%d.png", m_direction, 0)->getCString()));
}
