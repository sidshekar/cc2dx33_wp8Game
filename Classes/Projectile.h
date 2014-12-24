#ifndef __wp8Game__Proejctile__
#define __wp8Game__Projectile__

#pragma once
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class Projectile : public Sprite
{
public:

	Vec2 _speed;

	static Projectile* createProjectile(string filename, Vec2 p, Vec2 speed, string name);
	bool initProjectile(string filename, Vec2 p, Vec2  speed, string name);
	
	void shoot(float dt);
	void update();	
};
	

#endif 