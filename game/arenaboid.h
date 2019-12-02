
#ifndef ARENABOID_H
#define ARENABOID_H

#include <rt2d/entity.h>

#include "color.h"
#include "random.h"



class ArenaBoid : public Entity
{
public:
	/// @brief Constructor
	ArenaBoid(RGBAColor boidColor = RGBAColor(255,0,0));
	/// @brief Destructor
	virtual ~ArenaBoid();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	/// @brief handles all the input needed to control the boid.
	void handleInput(float inputSet = 1);
	/// @brief Applies force in a direction onto the boid.
	void applyForce(Vector2 force);
	/// @brief Simply rotates the boid on the Z-Axis.
	void turn(float a);
	/// @brief Calculates the force and then calls applyForce to apply the force.
	void thrust(float speed);
	///
	void wrapEdges(float sWidth, float sHeight);

	bool thrusting = false;

private:

	Vector2 pos;
	Vector2 vel;
	Vector2 accel;

	float damping = 0.9955f;
	float topSpeed = 3;
	float heading = 0;
	float r = 2;
	float rotationSpeed = 8;
	float speed = 3;
};

#endif /* ARENA_BOID_H */
