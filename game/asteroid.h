#ifndef ASTEROID_H
#define ASTEROID_H

#include "entity.h"
#include "shape.h"
#include "collider.h"
#include "random.h"

class Asteroid : public Entity {
public:
	Asteroid();
	virtual void update(float deltaTime);
	Circle circleCollisionShape = Circle(0, 0, 32);
private:
	Vector2 pos = Vector2(0,0);
	Vector2 accel = Vector2(0,0);
	Shape* collisionShape = 0;
	float heading = 0;
	void wrapEdges();
	float randomScale;

};
#endif /* ASTEROID_H */