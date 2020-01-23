#ifndef WEAPON_H
#define WEAPON_H

#include "entity.h"

class Weapon : public Entity
{
public:
	Weapon();
	virtual void update(float deltaTime);
	virtual void fire(float dir, Vector2 firePos, RGBAColor projectileColor);
	float fireRate = 1;
	float ammo = 30;
};

#endif /* WEAPON_H */