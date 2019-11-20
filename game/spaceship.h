
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <rt2d/entity.h>
#include "pointx.h"


class Spaceship : public Entity
{
public:
	/// @brief Constructor
	Spaceship(Point pos);
	/// @brief Destructor
	virtual ~Spaceship();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	void applyForce(Vector2 force);
	void turn(float a);
	void thrust(float speed);

private:
};

#endif /* SPACESHIP_H */
