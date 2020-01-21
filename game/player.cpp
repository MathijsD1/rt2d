#include "player.h"


Player::Player(RGBAColor playerColor) : Entity()
{
	this->heading = 0;

	pos = Point(Random().getRandomBetween(0, SWIDTH), Random().getRandomBetween(0, SHEIGHT));

	this->addSprite("assets/player.tga");
	this->sprite()->filter(0);
	this->sprite()->color = playerColor;

	float scale = 2;
	this->scale = Point3(scale, scale, scale);


	vel = Vector2(0, 0);
	accel = Vector2(0, 0);

	RGBAColor circleColor = playerColor;
	circleColor.a = 30;

	collisionShape = new Shape();
	collisionShape->position = this->position;
	Line c1;
	c1.color = circleColor;
	c1.createCircle(collisionSpan, 100);
	collisionShape->addLine(&c1);
	this->addChild(collisionShape);
}

Player::~Player()
{
	delete collisionShape;
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
		if (input()->getKey(KeyCode::Space) && this->weapon != nullptr) {
			this->weapon->fire(this->heading, this->pos, this->sprite()->color);
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
		if (input()->getKey(KeyCode::KeyPad2) && this->weapon != nullptr) {
			this->weapon->fire(this->heading, this->pos, this->sprite()->color);
		}
	}
}

void Player::update(float deltaTime)
{
	if (weapon != nullptr && weapon->ammo <= 0) {
		removeWeapon();
	}

	dTime = deltaTime;

	circleCollisionShape = Circle(this->position.x, this->position.y, collisionSpan);

	float width = SWIDTH;
	float height = SHEIGHT;

	wrapEdges(width, height);


	this->position = pos;

	vel += accel * dTime;
	vel *= damping;

	vel.limit(topSpeed);

	this->rotation = Point3(this->rotation.x,this->rotation.y, heading);

	pos += vel * dTime;

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
	force *= speed;
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

void Player::addWeapon(Weapon* weaponToAdd) {

	this->weapon = weaponToAdd;
	this->weapon->position += Point3(0, 5);

	this->addChild(weapon);
}

void Player::removeWeapon() 
{
	if (weapon != nullptr) 
	{
		this->removeChild(weapon);
		delete this->weapon;
		weapon = nullptr;
	}
}
