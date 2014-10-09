#include "Player.h"


bool Player::init()
{
	m_direction = 1;
	m_isRunning = true;
	//��ʼ�����Ƕ���
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_frameCache->addSpriteFramesWithFile("Player.plist", "Player.png"); //�����ܶ�ͼƬ����
	m_frameCache->retain();
	

	for (int i = 0; i < 4; i++)
	{
		
		CCSpriteFrame * frame = NULL;
		CCArray *frameList = CCArray::create();
		//��������֡������ӵ��б���
		for (int j = 0; j < 4; j++)
		{
			frame = m_frameCache->spriteFrameByName(CCString::createWithFormat("Player_%d_%d.png", i, j)->getCString());
			frameList->addObject(frame);
		}
		
		//���ݾ���֡���󴴽���������

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frameList);
		animation->setLoops(-1); //ѭ������ -1Ϊ����ѭ��
		animation->setDelayPerUnit(0.2f);//ÿһ֡���ŵļ��

		//������������
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
	
	//����ִ�ж���
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
