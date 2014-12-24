#include "Projectile.h"
#include "HelloWorldScene.h"

Projectile* Projectile::createProjectile(string filename, Vec2 p, Vec2 speed, string name)
{
	Projectile* ob = new Projectile();
	if(ob && ob->initProjectile(filename, p, speed, name))
    {
        ob->autorelease();

        return ob;
    }
    
    CC_SAFE_DELETE(ob);
    return NULL;
    
}

bool Projectile::initProjectile(string filename, Vec2 p, Vec2 speed, string name)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	_speed = speed;
	this->setName(name);

	this->initWithFile(filename);		
	this->setPosition(p);

	if (this->getName() == "enemy"){

		//enemy animation       
		CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("enemy_anim.png");

		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("enemy_anim.plist");

		this->createWithSpriteFrameName("enemy_idle_1.png");
		this->addChild(spritebatch);

		//idle animation		
		Vector <SpriteFrame*> animFrames;
		
		char str1[100] = { 0 };

		for (int i = 1; i <= 4; i++){
			sprintf(str1, "enemy_idle_%d.png", i);
			CCSpriteFrame* frame = cache->spriteFrameByName(str1);
			animFrames.pushBack(frame);
		}

		CCAnimation* idleanimation = CCAnimation::createWithSpriteFrames(animFrames, 0.25f);
		this->runAction(CCRepeatForever::create(CCAnimate::create(idleanimation)));

		this->schedule(schedule_selector(Projectile::shoot), 3.0);
	}

	return true;
}

void Projectile::update()
{
	Vec2 curPos = this->getPosition();
	Vec2 newPos = ccpAdd(curPos, _speed);
	this->setPosition(newPos);
}

void Projectile::shoot(float dt){

	//CCLog("[Enemy] shoot");
	Vec2 p = this->getPosition();
	p.x = p.x - this->getContentSize().width / 2;
	p.y = p.y - this->getContentSize().height * 0.05;

	HelloWorld* helloWorld = (HelloWorld*) this->getParent();
	helloWorld->shoot(p);
}


 