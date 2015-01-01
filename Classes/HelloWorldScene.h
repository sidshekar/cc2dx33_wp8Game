#ifndef __wp8Game__HELLOWORLD_SCENE_H__
#define __wp8Game__HELLOWORLD_SCENE_H__

#include "cocos2d.h"
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

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* scene();
	CREATE_FUNC(HelloWorld);
    virtual bool init();      
	void GameOver();
	void gamePaused();

	//variables
	int score;
	bool gameOver;
	cocos2d::Size visibleSize;
	cocos2d::Sprite* hero;
	vector<Projectile*> rockets;
	vector<Projectile*> enemies;
	vector<Projectile*> bullets;
	cocos2d::Vec2 gravity, thrust;
	ActionState mActionState; 
	PlayerState mPlayerState;	
	cocos2d::Action* mIdleAction, *mBoostAction;
	HUDLayer* hudLayer;
	ScrollingBgLayer* scrollingBgLayer;
	cocos2d::ParticleSystemQuad* flameParticle, *smokeParticle, *dustParticle;

	//functions
	virtual void update(float dt);
	void spawnEnemy(float dt);
	void fireRocket();
	void shoot(cocos2d::Vec2 position);
	void checkCollision();
	void gameResumed();
	void mainMenuScene(cocos2d::Object* pSender);
	void initHeroAnimation();
	void idleAnim();
	void boostAnim();
	void AnimationStates();
	void updateGameObjects();
	bool onTouchesBegan(cocos2d::Touch* touch, cocos2d::Event* event);    
};

#endif // __HELLOWORLD_SCENE_H__
