
#include "ParticleLayer.h"
USING_NS_CC;

ParticleLayer::ParticleLayer(Vec2 p)
{
	enemyDie = ParticleSpin::create(p, "EnemyDie.png");
	this->addChild(enemyDie);

	enemyGun = ParticleSpin::create(p, "EnemyGun.png");
	this->addChild(enemyGun);

	this->scheduleOnce( schedule_selector(ParticleLayer::removeSelf),2.0);
	this->schedule( schedule_selector(ParticleLayer::update));
}

ParticleLayer::~ParticleLayer(){
}

void ParticleLayer::update(float dt)
{
	enemyDie->update(dt);
	enemyGun->update(dt);    
}

void ParticleLayer::removeSelf(float dt)
{
	this->unscheduleUpdate();
	this->removeFromParent();
}
