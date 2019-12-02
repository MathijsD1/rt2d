#include "player.h"

//delta time
float dTime;


Player::Player(RGBAColor boidColor) : Entity()
{
	pos = Point(Random().getRandomBetween(0, SWIDTH), Random().getRandomBetween(0, SHEIGHT));

	this->addSprite("assets/player.tga");
	this->sprite()->filter(1);
	this->sprite()->color = boidColor;

	float scale = 1.3f;
	this->scale = Point3(scale, scale, scale);


	vel = Vector2(0, 0);
	accel = Vector2(0, 0);

	std::cout << "Created new player" << std::endl;

	RGBAColor circleColor = boidColor;
	circleColor.a = 20;

	collisionShape = new Shape();
	collisionShape->position = this->position;
	Line c1;
	c1.color = circleColor;
	c1.createCircle(collisionSpan, 20);
	collisionShape->addLine(&c1);
	this->addChild(collisionShape);
}

Player::~Player()
{

}

void Player::handleInput(float inputSet)
{
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

void Player::update(float deltaTime)
{
	circleCollisionShape = Circle(this->position.x, this->position.y, collisionSpan);

	float width = SWIDTH;
	float height = SHEIGHT;

	wrapEdges(width, height);

	dTime = deltaTime;

	this->position = pos;

	vel += accel;
	vel *= damping;

	vel.limit(topSpeed);

	this->rotation = Point3(this->rotation.x,this->rotation.y, heading);

	pos += vel;

	accel *= 0;
}

void Player::applyForce(Vector2 force)
{
	Vector2 f = force;
	accel += f;
}

void Player::turn(float a)
{
	heading += a;
}

void Player::thrust(float speed = 1)
{
	float angle = heading - PI / 2;
	Vector2 force = Vector2(cos(angle), sin(angle));
	force *= speed * dTime;
	applyForce(force);
	thrusting = true;
}

void Player::wrapEdges(float sWidth, float sHeight) {
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
