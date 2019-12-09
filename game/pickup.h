#ifndef PICKUP_H
#define PICKUP_H

#include <rt2d/entity.h>
#include "shape.h"
#include "collider.h"
#include "random.h"

class Pickup : public Entity
{
public:
	Pickup();

	Circle circleCollisionShape = Circle(0, 0, 32);
private:
	Shape* collisionShape;

	void update(float deltaTime);

};

#endif /* PICKUP_H */
