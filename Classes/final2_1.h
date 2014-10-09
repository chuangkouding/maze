
#ifndef __final2_1_H__
#define __final2_1_H__

#include "cocos2d.h"
using namespace cocos2d;
#include "MainmenuScene.h"
#include "final2.h"

class final2_1 : public CCLayer {
public:
	static CCScene* scene();
	virtual bool init();
    void menuCloseCallback(CCObject* pSender);
	void menuCallback(CCObject* pSender);

	CREATE_FUNC(final2_1);
};

#endif