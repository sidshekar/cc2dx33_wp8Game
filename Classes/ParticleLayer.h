

#ifndef __wp8Game__ParticleLayer__
#define __wp8Game__ParticleLayer__

#include <iostream>

#include "cocos2d.h"
#include "ParticleSpin.h"

class ParticleLayer: public cocos2d::Layer
{

public:
	ParticleLayer(cocos2d::Vec2 p);
    ~ParticleLayer();  

	ParticleSpin* enemyDie;
	ParticleSpin* enemyGun;

	void removeSelf(float dt);  
    void update(float dt);
};

#endif /* defined(__sdpdd__ProjectileSpin__) */
