#include "Projectile.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Projectile* Projectile::createProjectile(string filename, Vec2 p, Vec2 speed, string name)
{
	auto ob = new Projectile();
	if(ob && ob->initProjectile(filename, p, speed, name))
    {
        ob->autorelease();

        return ob;
    }
    
    CC_SAFE_DELETE(ob);
    return nullptr;
    
}

bool Projectile::initProjectile(string filename, Vec2 p, Vec2 speed, string name)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_speed = speed;
	this->setName(name);

	this->initWithFile(filename);		
	this->setPosition(p);

	if (this->getName() == "enemy"){

		//enemy animation       
		auto spritebatch = SpriteBatchNode::create("enemy_anim.png");

		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("enemy_anim.plist");

		this->createWithSpriteFrameName("enemy_idle_1.png");
		this->addChild(spritebatch);

		//idle animation		
		Vector <SpriteFrame*> animFrames;
		
		char str1[100] = { 0 };

		for (int i = 1; i <= 4; i++){
			sprintf(str1, "enemy_idle_%d.png", i);
			auto frame = cache->getSpriteFrameByName(str1);
			animFrames.pushBack(frame);
		}

		Animation* idleanimation = Animation::createWithSpriteFrames(animFrames, 0.25f);
		this->runAction(RepeatForever::create(Animate::create(idleanimation)));
		this->schedule(schedule_selector(Projectile::shoot), 3.0);
	}

	return true;
}

void Projectile::update()
{
	Vec2 curPos = this->getPosition();
	Vec2 newPos = curPos + _speed;
	this->setPosition(newPos);
}

void Projectile::shoot(float dt){

	Vec2 p = this->getPosition();
	p.x = p.x - this->getContentSize().width / 2;
	p.y = p.y - this->getContentSize().height * 0.05;

	auto helloWorld = dynamic_cast<HelloWorld*>(this->getParent());
	helloWorld->shoot(p);
}


 