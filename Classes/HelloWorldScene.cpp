#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"


CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }    

	gravity = Vec2(0, -1.0);
	thrust = Vec2(0, 0);
	gameOver = false;
	score = 0;

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();    
	Vec2 origin = CCDirector::sharedDirector()->getVisibleOrigin();

	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);

	hero = Sprite::create("bookGame_tinyBazooka.png");
	hero->setPosition(Vec2(visibleSize.width * 0.125, visibleSize.height * 0.5));
	addChild(hero, 5);
	initHeroAnimation();

	flameParticle = CCParticleSystemQuad::create("jetBoost.plist");
	flameParticle->setPosition(ccpAdd(hero->getPosition(), ccp(-hero->getContentSize().width * 0.25, 0)));
	addChild(flameParticle);
	
	hudLayer = new HUDLayer();
	this->addChild(hudLayer, 15); //keeping at top most layer

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);	

	this->scheduleUpdate();    
	this->schedule(schedule_selector(HelloWorld::spawnEnemy),3.0);

    return true;
}


void HelloWorld::update(float dt)
{

	if(!gameOver)
	{

		scrollingBgLayer->update();
		updateGameObjects();
		checkCollision();

		flameParticle->setPosition(ccpAdd(hero->getPosition(), ccp(-hero->getContentSize().width * 0.25, 0)));


		thrust.y += gravity.y;
		float yVelocity = hero->getPosition().y + thrust.y;
		hero->setPosition(Vec2(hero->getPosition().x, yVelocity));

		float maxY = visibleSize.height - hero->getContentSize().height/2;
		float minY = hero->getContentSize().height/2;
 
		float newY = hero->getPosition().y ;
		newY = MIN(MAX(newY, minY), maxY);

		if (hero->getPositionY() > maxY || hero->getPositionY() < minY)
			thrust.y = 0;
		
		hero->setPosition(ccp(hero->getPosition().x, newY));
		
		if (thrust.y > 0)
			mPlayerState = kPlayerStateBoost;
		else
			mPlayerState = kPLayerStateIdle;

		this->AnimationStates();


		/*
		if(jump)
		{
			jumpTimer = 10;
			jump = false;

		}

		if(jumpTimer>0)
		{
			CCLog("boost");

			mPlayerState = kPlayerStateBoost;
			jumpTimer--;
			CCPoint p = hero->getPosition();
			CCPoint mP = ccpAdd(p,ccp(0,7));
			hero->setPosition(mP);
		}
		else
		{
			CCLog("idle");
			
			mPlayerState = kPLayerStateIdle;
			jumpTimer = 0;
			CCPoint p = hero->getPosition();
			CCPoint pM = ccpAdd(p,gravity);
			hero->setPosition(pM);
		}

		*/

	}
	else
	{
		GameOver();
	}

}//update 

void HelloWorld::updateGameObjects(){


	for (int i = 0; i<rockets.size(); i++)
	{
		Projectile* p = (Projectile*)rockets[i];
		p->update();

		if (p->getPositionX() >= visibleSize.width){
			this->removeChild(p);
			rockets.erase(rockets.begin() + i);
		}
	}

	//enemies
	for (int i = 0; i <enemies.size(); i++)
	{
		Projectile* e = (Projectile*)enemies[i];
		e->update();

		if (e->getPositionX() + e->getContentSize().width / 2 < 0)
		{
			enemies.erase(enemies.begin() + i);
			GameOver();
		}
	}


	for (int i = 0; i<bullets.size(); i++)
	{
		Projectile* p = (Projectile*)bullets[i];
		p->update();

		if (p->getPositionX() <= 0)
		{
			this->removeChild(p);
			bullets.erase(bullets.begin() + i);
		}
	}
}

void HelloWorld::checkCollision(){

	//** collisions and scoring **
	//player rocket and enemies collision

	for (int i = 0; i<rockets.size(); i++)
	{
		Projectile* rocket = (Projectile*)rockets[i];

		for (int j = 0; j< enemies.size(); j++)
		{
			Projectile* enemy = (Projectile*)enemies[j];

			//CCLog("player rocket and enemy");
			
			if (rocket->boundingBox().intersectsRect(enemy->boundingBox()))
			{
				score++;

				hudLayer->updateScore(score);

				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemyKill.wav");
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("rocketExplode.wav");

				ParticleLayer* pLayer = new ParticleLayer(enemy->getPosition());
				this->addChild(pLayer);

				//smokeParticle = CCParticleSystemQuad::create("smoke.plist");
				//smokeParticle->setPosition(enemy->getPosition());
				//this->addChild(smokeParticle, 15);   
				//smokeParticle->setAutoRemoveOnFinish(true);

				//dustParticle = CCParticleSystemQuad::create("dusts.plist");
				//dustParticle->setPosition(enemy->getPosition());
				//this->addChild(dustParticle, 15);   
				//dustParticle->setAutoRemoveOnFinish(true);


				this->removeChild(rocket);
				this->removeChild(enemy);

				rockets.erase(rockets.begin() + i);
				enemies.erase(enemies.begin() + j);

				return;
			}
		}
	}
	

	//enemy bullets and player

		for (int i = 0; i < bullets.size(); i++)
		{
			Projectile* b = (Projectile*)bullets[i];

			//CCLog("enemy bullet and player");
			
			if (b->boundingBox().intersectsRect(hero->boundingBox()))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("playerKill.wav");

				this->removeChild(b);
				bullets.erase(bullets.begin() + i);
				
				GameOver();

				return;
			}
		}
	



}

void HelloWorld::GameOver()
{

	gameOver = true;

	
	//CCLog("Game Over!!!!");

		this->unscheduleAllSelectors();
		
		for (int i = 0; i< enemies.size(); i++){
			Projectile* en = (Projectile*)enemies[i];
			en->unscheduleAllSelectors();
		}
		

	CCMenuItemImage*mainmenuItem = CCMenuItemImage::create("_bookgame_UI_mainmenu.png",
														 "_bookgame_UI_mainmenu.png", this,
														 menu_selector(HelloWorld::mainMenuScene));
    
	mainmenuItem->setPosition(ccp(visibleSize.width/2,
								visibleSize.height * 0.2));
	
	
	CCMenu *mainMenu = CCMenu::create(mainmenuItem, NULL);
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	CCLabelBMFont* gameOverLabel = CCLabelBMFont::create("GAMEOVER", "PixelFont.fnt");
	gameOverLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.6));
	this->addChild(gameOverLabel, 10);

	int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bazookaGameHighScore");

	if(score > highScore)
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("bazookaGameHighScore", score);
        CCUserDefault::sharedUserDefault()->flush();
        
        CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create("NEW HIGH SCORE", "PixelFont.fnt");
        newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
        this->addChild(newHighScoreLabel, 10);
        newHighScoreLabel->setScale(0.75);
        
        CCLabelBMFont* GOscoreLabel = CCLabelBMFont::create("0", "PixelFont.fnt");
        GOscoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.4));
        this->addChild(GOscoreLabel, 10);
        GOscoreLabel->setScale(0.75);        
        
        char scoreTxt[100];
        sprintf(scoreTxt, "%d", score);
        GOscoreLabel->setString(scoreTxt);
        
    }
    else
    {
        CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create("BETTER LUCK NEXT TIME", "PixelFont.fnt");
        newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
        this->addChild(newHighScoreLabel, 10);
        newHighScoreLabel->setScale(0.75);    
    } 

}


void HelloWorld::spawnEnemy(float dt)
{
	//CCLog("spawn enemy");

	float mrand = rand() % 3 + 1;
	float h = visibleSize.height * mrand * 0.25;

	Sprite* eSprite = Sprite::create("bookGame_enemy.png");
	Vec2 pos = Vec2(visibleSize.width + eSprite->getContentSize().width / 2, h);

	Projectile* e = Projectile::createProjectile("bookGame_enemy.png", pos, Vec2(-2,0),"enemy");
	addChild(e);
	e->shoot(0.016);

	enemies.push_back(e);
}

void HelloWorld::shoot(Vec2 position)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("gunshot.wav");

	Projectile* pr = Projectile::createProjectile("bookGame_bullet.png", position, Vec2(-5, 0), "bullet");
	addChild(pr);

	bullets.push_back(pr);
}


void HelloWorld::fireRocket()
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("fireRocket.wav");
	
	Vec2 p = hero->getPosition();

	p.x = p.x + hero->getContentSize().width/2;
	p.y = p.y - hero->getContentSize().height * 0.05;

	Projectile* rocket = Projectile::createProjectile("bookGame_rocket.png",p,Vec2(10,0), "rocket");
	addChild(rocket);

	rockets.push_back(rocket);

	//CCParticleFire: Point particle system. Uses Gravity mode.
	//CCParticleFireworks: Point particle system. Uses Gravity mode.
	//CCParticleSun: Point particle system. Uses Gravity mode.
	//CCParticleGalaxy: Point particle system. Uses Gravity mode.
	//CCParticleFlower: Point particle system. Uses Gravity mode.
	//CCParticleMeteor: Point particle system. Uses Gravity mode.
	//CCParticleSpiral: Point particle system. Uses Gravity mode.
	//CCParticleExplosion: Point particle system. Uses Gravity mode.
	//CCParticleSmoke: Point particle system. Uses Gravity mode.
	//CCParticleSnow: Point particle system. Uses Gravity mode.
	//CCParticleRain: Point particle system. Uses Gravity mode.

	//CCParticleSystemQuad*m_emitter = CCParticleExplosion::create();
	//m_emitter->retain();
	//m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("smoke.png"));

	//m_emitter->setPosition(ccpAdd(hero->getPosition(), Vec2(hero->getContentSize().width / 2, 0)));
	
	//m_emitter->setStartColor(ccc4f(1.0, 1.0, 1.0, 1.0));
	//m_emitter->setEndColor(ccc4f(0.0, 0.0, 0.0, 0.0));
	
	//m_emitter->setTotalParticles(10);
	//m_emitter->setLife(0.25);
	//m_emitter->setSpeed(2.0);
	//m_emitter->setSpeedVar(50.0);
	
	//** gravity
	//m_emitter->setEmitterMode(kCCParticleModeGravity);
	//m_emitter->setGravity(ccp(0,90));
	
	//** mode radius
	//m_emitter->setEmitterMode(kCCParticleModeRadius);
	//m_emitter->setStartRadius(0);
	//m_emitter->setStartRadiusVar(50);
	//m_emitter->setRotatePerSecond(2);
	//m_emitter->setRotatePerSecondVar(5);

	//this->addChild(m_emitter, 0);
	//m_emitter->setAutoRemoveOnFinish(true);

	smokeParticle = CCParticleSystemQuad::create("smoke.plist");
	smokeParticle->setPosition(p);
	this->addChild(smokeParticle);
}


void HelloWorld::gamePaused()
{
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(HelloWorld::spawnEnemy));
	
	for(int i=0; i< enemies.size(); i++){
		Projectile* en = (Projectile*)enemies[i];
		en->pauseSchedulerAndActions();
	}
	
}

void HelloWorld::gameResumed()
{
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy),3.0);

	for(int i=0; i< enemies.size(); i++){
		Projectile* en = (Projectile*)enemies[i];
		en->resumeSchedulerAndActions();
	}	
}

void HelloWorld::mainMenuScene(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	
	CCScene *mScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}

# pragma - mark Touches
bool HelloWorld::onTouchesBegan(Touch* touch, Event* event)
{

	CCPoint location = touch->getLocationInView();

	location = CCDirector::sharedDirector()->convertToGL(location);


	if(!gameOver)
	{
		
		if (location.x < visibleSize.width / 2){
		
			//Jump
			thrust.y = 15.0f;

		}
		else{
		
			fireRocket();
		}		
	}

	return true;
}



void HelloWorld::initHeroAnimation(){

	//player animation       
	CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("player_anim.png");
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("player_anim.plist");

	hero->createWithSpriteFrameName("player_idle_1.png");
	hero->addChild(spritebatch);

	//idle animation
	Vector<SpriteFrame*> animFrames;

	char str1[100] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str1, "player_idle_%d.png", i);
		SpriteFrame* frame = cache->spriteFrameByName(str1);
		animFrames.pushBack(frame);
	}

	Animation* idleanimation = Animation::createWithSpriteFrames(animFrames, 0.25f);
	mIdleAction = CCRepeatForever::create(CCAnimate::create(idleanimation));
	mIdleAction->retain();


	animFrames.clear();

	//boost animation
	char str2[100] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str2, "player_boost_%d.png", i);
		SpriteFrame* frame = cache->spriteFrameByName(str2);
		animFrames.pushBack(frame);
	}

	CCAnimation* boostanimation = CCAnimation::createWithSpriteFrames(animFrames, 0.25f);
	hero->runAction(CCRepeatForever::create(CCAnimate::create(boostanimation)));

	mBoostAction = CCRepeatForever::create(CCAnimate::create(boostanimation));
	mBoostAction->retain();
}

void HelloWorld::idleAnim()
{
	if (mActionState != kActionStateIdle)
	{
		hero->stopAllActions();
		hero->runAction(mIdleAction);
		mActionState = kActionStateIdle;
	}
}

void HelloWorld::boostAnim()
{
	if (mActionState != kActionStateBoost)
	{
		hero->stopAllActions();
		hero->runAction(mBoostAction);
		mActionState = kActionStateBoost;
	}
}

void HelloWorld::AnimationStates()
{
	CCLOG("action state");

	switch (mPlayerState)
	{
		case kPLayerStateIdle:
			this->idleAnim(); break;
		case kPlayerStateBoost:
			this->boostAnim(); break;
		default: break;
	}
}
