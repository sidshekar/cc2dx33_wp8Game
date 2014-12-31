
#ifndef __wp8Game__ParticleSpin__
#define __wp8Game__ParticleSpin__

class ProjectileObject;

#include <iostream>
#include "cocos2d.h"

class ParticleSpin: public cocos2d::Sprite
{
    ParticleSpin();
    ~ParticleSpin();
    
	cocos2d::Vec2 speed;
	cocos2d::Vec2 gravity;
    float spinCounter;
    
public:
	bool init();
    static ParticleSpin* create(cocos2d::Vec2 _cp, char *fileName);  
    void update(float dt);
};

#endif /* defined(__sdpdd__ProjectileSpin__) */
