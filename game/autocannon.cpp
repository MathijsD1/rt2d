#include "autocannon.h"

AutoCannon::AutoCannon() : Weapon()
{
	this->addSprite("assets/autocannon.tga");
	this->sprite()->filter(0);
	this->scale = Point2(0.55f, 0.55f);

	fireRate = 1;
	ammo = 200;
}

void AutoCannon::update(float deltaTime) 
{
	fireRate -= deltaTime * 85;
}

