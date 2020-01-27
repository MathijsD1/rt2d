#ifndef PLAYER_H
#define PLAYER_H

#include <rt2d/entity.h>


#include "color.h"
#include "random.h"
#include "collider.h"
#include "shape.h"
#include "weapon.h"

class Player : public Entity
{
public:
	/// @brief Constructor
	Player(RGBAColor playerColor = RGBAColor(255,0,0));
	/// @brief Destructor
	virtual ~Player();

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
	/// @brief Prevents the player from going out of screen.
	void wrapEdges(float sWidth, float sHeight);

	void addWeapon(Weapon* weaponToAdd);
	void removeWeapon();

	void damage(float amount) {

		if (amount < 0) {
			amount *= -1;
		}

		health -= amount;

		if (health < 0) {
			health = 0;
		}
	}

	void heal(float amount) {

		if (amount < 0) {
			amount *= -1;
		}

		health += amount;

		if (health > 100) {
			health = 100;
		}
	}

	bool isAlive() 
	{
		if (health > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	float getHealth()
	{
		return health;
	}

	//Used for Particle System later.
	bool thrusting = false;

	/// @brief Collision Shape used to detect if the player has collided with other colliders.
	Circle circleCollisionShape = Circle(0, 0, 32);

	Vector2 vel;

private:
	Vector2 pos = Vector2(0,0);
	Vector2 accel = Vector2(0,0);

	Shape* collisionShape = 0;
	Weapon* weapon = 0;

	float damping = 0.98f;
	float topSpeed = 1800;
	float heading = 0;
	float r = 2;
	float rotationSpeed = 4.5;
	float speed = 1800;
	float health = 100;
	float dTime = 0;

	int collisionSpan = 18;
};

#endif /* PLAYER_H */
