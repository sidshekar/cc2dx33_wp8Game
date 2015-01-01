
#ifndef __wp8Game__ScrollingBg__
#define __wp8Game__ScrollingBg__

#include <iostream>
#include "cocos2d.h"

using namespace std;

class ScrollingBg: public cocos2d::Layer
{
public:    
    static ScrollingBg* create(string name, float _speed, float _yPos);
    bool initScrollingBg(string _name, float _speed, float _yPos);    
    cocos2d::Sprite* gameBg1, *gameBg2;    
    float speed;
    string name;    
    cocos2d::Size winSize;    
    void update();    
};

#endif /* defined(__endlessFlyer__ScrollingBg__) */
