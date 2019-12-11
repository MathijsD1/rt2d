#ifndef PICKUP_H
#define PICKUP_H

#include <rt2d/entity.h>
#include "shape.h"
#include "collider.h"
#include "random.h"
#include "player.h"

class Pickup : public Entity
{
public:
	Pickup();
	void updateCollider();
	virtual void use(Player* p);

	Circle circleCollisionShape = Circle(0, 0, 32);
private:
	Shape* collisionShape;

	int collisionSpan = 18;

	void update(float deltaTime);

};

#endif /* PICKUP_H */
