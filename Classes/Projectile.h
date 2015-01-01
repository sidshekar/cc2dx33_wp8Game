#ifndef __wp8Game__Proejctile__
#define __wp8Game__Projectile__

#pragma once
#include "cocos2d.h"

class Projectile : public cocos2d::Sprite
{
public:

	cocos2d::Vec2 _speed;
	static Projectile* createProjectile(std::string filename, cocos2d::Vec2 p, cocos2d::Vec2 speed, std::string name);
	bool initProjectile(std::string filename, cocos2d::Vec2 p, cocos2d::Vec2  speed, std::string name);	
	void shoot(float dt);
	void update();	
};
	

#endif 