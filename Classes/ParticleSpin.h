
#ifndef __wp8Game__ParticleSpin__
#define __wp8Game__ParticleSpin__

class ProjectileObject;

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;


class ParticleSpin: public CCSprite
{
    ParticleSpin();
    ~ParticleSpin();
    
	CCPoint speed;
	CCPoint gravity;
    float spinCounter;
    
public:
	bool init();
    static ParticleSpin* create(Vec2 _cp, char *fileName);
  
    void update(float dt);
};

#endif /* defined(__sdpdd__ProjectileSpin__) */
