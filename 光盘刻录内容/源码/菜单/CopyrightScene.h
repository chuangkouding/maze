#ifndef __CopyrightScene_H__
#define __CopyrightScene_H__

#include "cocos2d.h"
//#include "RealSize.h" //

class CopyrightScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	//void menuCloseCallback(CCObject* pSender);
	void menuCloseCallback(float dt);
	virtual void keyBackClicked();  //返回键回调函数
	// implement the "static node()" method manually
	CREATE_FUNC(CopyrightScene);
};

#endif // __COPYRIGHTSCENE_H__
