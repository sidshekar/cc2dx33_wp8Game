
#include "ScrollingBg.h"
ScrollingBg* ScrollingBg::create(string _name, float _speed, float _yPos)
{
    ScrollingBg* ob = new ScrollingBg();
    if(ob && ob->initScrollingBg(_name, _speed, _yPos))
    {
        ob->autorelease();
        return ob;
    }
    
    CC_SAFE_DELETE(ob);
    return NULL;
    
}

bool ScrollingBg::initScrollingBg(string _name, float _speed, float _yPos)
{
	winSize = CCDirector::getInstance()->getWinSize();

	//CCLog("[ScrollingBG] winsizeX: %f, winSizeY: %f", winSize.width, winSize.height);
    
    speed = _speed;
    
    gameBg1 = Sprite::create(_name.c_str()); 
	gameBg1->setPosition(Vec2(winSize.width * 0.5f, _yPos));
    gameBg1->setAnchorPoint(Vec2(0.5,0.0));
    gameBg1->setScaleX(1.0);
    addChild(gameBg1);
    
    gameBg2 = Sprite::create(_name.c_str());
	gameBg2->setPosition(Vec2(winSize.width * 0.5f + winSize.width , _yPos));
    gameBg2->setAnchorPoint(Vec2(0.5,0.0));
    gameBg2->setScaleX(1.0);
    addChild(gameBg2);
    
    return true;
}

void ScrollingBg::update()
{

    // scroll bg left or right
    if(gameBg1->getPosition().x < - winSize.width/2 )
		gameBg1->setPosition(Vec2(winSize.width + winSize.width/2, gameBg1->getPosition().y));
    
    
    if(gameBg2->getPosition().x < - winSize.width/2 )
		gameBg2->setPosition(Vec2(winSize.width + winSize.width/2,gameBg2->getPosition().y));
    
    
	Vec2 bg1pos = gameBg1->getPosition();
	gameBg1->setPosition(Vec2((bg1pos.x - speed), bg1pos.y));
    
	Vec2 bg2pos = gameBg2->getPosition();
	gameBg2->setPosition(Vec2((bg2pos.x - speed), bg2pos.y));
    
}
