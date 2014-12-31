#ifndef __wp8Game__OPTIONSMENU_SCENE__
#define __wp8Game__OPTIONSMENU_SCENE__

#include "cocos2d.h"
#include "ScrollingBgLayer.h"

using namespace cocos2d;

class OptionsMenu : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    
	virtual bool init();  

	ScrollingBgLayer* scrollingBgLayer;
	MenuItemImage* soundOnItem;
	MenuItemImage* soundOffItem;
	static cocos2d::Scene* scene();
	void update(float dt);
	void reset(Object* pSender);
	void mainMenu(Object* pSender);
	void SoundOnOff(Object* sender);
	CREATE_FUNC(OptionsMenu);
};

#endif 
