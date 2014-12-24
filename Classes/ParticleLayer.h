

#ifndef __wp8Game__ParticleLayer__
#define __wp8Game__ParticleLayer__

#include <iostream>

#include "cocos2d.h"
#include "ParticleSpin.h"
using namespace cocos2d;

class ParticleLayer: public CCLayer
{

public:
	ParticleLayer(Vec2 p);
    ~ParticleLayer();  

	ParticleSpin* enemyDie;
	ParticleSpin* enemyGun;

	void removeSelf(float dt);  
    void update(float dt);
};

#endif /* defined(__sdpdd__ProjectileSpin__) */
