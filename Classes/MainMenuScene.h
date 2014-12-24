#ifndef __wp8Game__MAINMENU_SCENE__
#define __wp8Game__MAINMENU_SCENE__

#include "cocos2d.h"
#include "ScrollingBgLayer.h"

using namespace cocos2d;

class MainMenu : public cocos2d::Layer
{
public:
    
	virtual bool init(); 
	void update(float dt);

	ScrollingBgLayer* scrollingBgLayer;
	
	void optionsScene(Ref* pSender);
	void playGame(Ref* pSender);
	
	static cocos2d::Scene* scene();
	
	CREATE_FUNC(MainMenu);
};

#endif 
