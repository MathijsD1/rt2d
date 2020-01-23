#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include "collider.h"
#include "shape.h"

class Projectile : public Entity
{
public:
	Projectile();
	virtual void update(float deltaTime);
	float heading = 0;
	bool isOutOfScreen = false;
	Circle circleCollisionShape = Circle(0, 0, 32);
private:
	Shape* collisionShape = 0;
	void cull();
	
};

#endif /* PROJECTILE_H */