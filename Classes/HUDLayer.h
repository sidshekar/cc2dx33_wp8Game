#ifndef __wp8Game__HUDLayer__
#define __wp8Game__HUDLayer__

#pragma once
#include "cocos2d.h"

class HelloWorldScene;

class HUDLayer : public cocos2d::Layer
{
public:
	HUDLayer(void);
	~HUDLayer(void);
	void updateScore(int score);
	cocos2d::Menu* pauseMenu;
	cocos2d::Menu* resumeMenu;
	cocos2d::Size visibleSize;
	cocos2d::Label* scoreLabel;
	void pauseGame(cocos2d::Object* pSender);
	void resumeGame(cocos2d::Object* pSender);	
};
	

#endif 