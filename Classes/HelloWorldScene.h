#ifndef __wp8Game__HELLOWORLD_SCENE_H__
#define __wp8Game__HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

USING_NS_CC;


#include "ParticleLayer.h"
#include "Projectile.h"
#include "HUDLayer.h"
#include "ScrollingBgLayer.h"
#include <spine/spine-cocos2dx.h>

typedef enum ActionState 
{
	kActionStateNone = 0,
	kActionStateIdle ,
	kActionStateBoost
};

typedef enum PlayerState 
{
	kPlayerStateNone = 0,
	kPLayerStateIdle,
	kPlayerStateBoost
};

class HelloWorld : public cocos2d::CCLayer
{
public:

	//variables
	int score;
	bool gameOver;

	Size visibleSize;
	Sprite* hero;

	vector<Projectile*> rockets;
	vector<Projectile*> enemies;
	vector<Projectile*> bullets;

	Vec2 gravity, thrust;

	ActionState mActionState; 
	PlayerState mPlayerState;
	
	CCAction* mIdleAction, *mBoostAction;

	HUDLayer* hudLayer;
	ScrollingBgLayer* scrollingBgLayer;

	CCParticleSystemQuad* flameParticle, *smokeParticle, *dustParticle;

	//functions
	virtual void update(float dt);
	void spawnEnemy(float dt);
	void fireRocket();
	void shoot(Vec2 position);
	void GameOver();
	void checkCollision();
	void gamePaused();
	void gameResumed();
	void mainMenuScene(CCObject* pSender);

	void initHeroAnimation();
	void idleAnim();
	void boostAnim();
	void AnimationStates();

	void updateGameObjects();


	//virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual bool onTouchesBegan(Touch* touch, Event* event);

    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
