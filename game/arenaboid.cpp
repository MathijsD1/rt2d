#include "arenaboid.h"

float dTime;



ArenaBoid::ArenaBoid(RGBAColor boidColor = RGBAColor(255,255,255)) : Entity()
{
	pos = Point(SWIDTH/2, SHEIGHT/2);

	this->addSprite("assets/boid.tga");
	this->sprite()->filter(2);
	this->sprite()->color = boidColor;


	vel = Vector2(0, 0);
	accel = Vector2(0, 0);

}

ArenaBoid::~ArenaBoid()
{

}

void ArenaBoid::handleInput(float inputSet)
{
	float speed = 2.5f;

	//Default input
	if (inputSet == 1) 
	{
		if (input()->getKey(KeyCode::A)) {
			turn(-rotationSpeed * dTime);
		}
		if (input()->getKey(KeyCode::D)) {
			turn(rotationSpeed * dTime);
		}
		if (input()->getKey(KeyCode::W)) {
			thrust(speed);
		}
	}

	//Keypad input
	if (inputSet == 2)
	{
		if (input()->getKey(KeyCode::KeyPad1)) {
			turn(-rotationSpeed * dTime);
		}
		if (input()->getKey(KeyCode::KeyPad3)) {
			turn(rotationSpeed * dTime);
		}
		if (input()->getKey(KeyCode::KeyPad5)) {
			thrust(speed);
		}
	}
}

void ArenaBoid::update(float deltaTime)
{
	float width = SWIDTH;
	float height = SHEIGHT;

	wrapEdges(width, height);

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

void ArenaBoid::applyForce(Vector2 force)
{
	Vector2 f = force;
	accel += f;
}

void ArenaBoid::turn(float a)
{
	heading += a;
}

void ArenaBoid::thrust(float speed = 1)
{
	float angle = heading - PI / 2;
	Vector2 force = Vector2(cos(angle), sin(angle));
	force *= speed * dTime;
	applyForce(force);
	thrusting = true;
}

void ArenaBoid::wrapEdges(float sWidth, float sHeight) {
	float buffer = r * 2;

	if (pos.x > sWidth + buffer) {
		pos.x = -buffer;
	}

	if (pos.x < -buffer) {
		pos.x = sWidth + buffer;
	}

	if (pos.y > sHeight + buffer) {
		pos.y = -buffer;
	}

	if (pos.y < -buffer) {
		pos.y = sHeight + buffer;
	}
}
