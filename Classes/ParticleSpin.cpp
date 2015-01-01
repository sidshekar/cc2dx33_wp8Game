
#include "ParticleSpin.h"
USING_NS_CC;

ParticleSpin::ParticleSpin()
{
	spinCounter = 0;
}

ParticleSpin::~ParticleSpin()
{}

ParticleSpin* ParticleSpin::create(Vec2 _cp, char *fileName)
{
    auto pc = new ParticleSpin();
    if(pc && pc->initWithFile(fileName))
    {
        pc->setPosition(_cp);
        pc->init();
        pc->autorelease();
        return pc;
	}
    
    CC_SAFE_DELETE(pc);
    return nullptr;
}

bool ParticleSpin::init()
{
 
    Size winSize = Director::getInstance()->getWinSize();    
    gravity = Vec2(0,-0.25);    
    speed.x = CCRANDOM_MINUS1_1() * 2.0f;
    speed.y = rand()% 3 + 1 ;    
    log("speed x %f", speed.x);    
    return true;
}


void ParticleSpin::update(float dt)
{
    spinCounter += dt*4;    
    Vec2 initpos = this->getPosition();    
    Vec2 finalpos;
    finalpos.x = initpos.x + speed.x;
    speed.y += gravity.y;
    finalpos.y = initpos.y + speed.y + gravity.y;    
    this->setPosition(finalpos);    
    this->setRotation(CC_RADIANS_TO_DEGREES(spinCounter * speed.x));      
}
