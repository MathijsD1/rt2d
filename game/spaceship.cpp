#include "spaceship.h"

Vector2 pos;
Vector2 vel;
Vector2 accel;


float damping = 0.9995;
float topSpeed = 3;
float dTime;
float heading = 0;
float r = 16;
float rotationSpeed = 8;

bool thrusting = false;



Spaceship::Spaceship(Point posG) : Entity()
{
	pos = posG;

	this->addSprite("assets/boid.tga");
	this->sprite()->filter(1);
	this->sprite()->color = YELLOW;
	this->scale = Point3(2, 2, 2);

	vel = Vector2(0, 0);
	accel = Vector2(0, 0);

}

Spaceship::~Spaceship()
{
	
}

void Spaceship::update(float deltaTime)
{
	if (input()->getKey(KeyCode::A)) {
		turn(-rotationSpeed * deltaTime);
	}
	if (input()->getKey(KeyCode::D)) {
		turn(rotationSpeed * deltaTime);
	}
	if (input()->getKey(KeyCode::W)) {
		thrust(1);
	}

	dTime = deltaTime;

	this->position = pos;

	vel += accel;
	vel *= damping;

	vel.limit(topSpeed);

	float a = heading - 89.5f;
	this->rotation = Point3(this->rotation.x,this->rotation.y, a);

	pos += vel;

	accel *= 0;
}

void Spaceship::applyForce(Vector2 force) 
{
	Vector2 f = force;
	accel += f;
}

void Spaceship::turn(float a)
{
	heading += a;
}

void Spaceship::thrust(float speed = 1) 
{
	float angle = heading - PI / 2;
	Vector2 force = Vector2(cos(angle), sin(angle));
	force *= speed * dTime;
	applyForce(force);
	thrusting = true;
}