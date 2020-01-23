#include "projectile.h"

Projectile::Projectile() : Entity()
{
	this->addSprite("assets/projectile.tga");

	collisionShape = new Shape();
	collisionShape->position = this->position;

	Line c1;
	c1.color = this->sprite()->color;
	c1.createCircle(8, 100);
	collisionShape->addLine(&c1);
	this->addChild(collisionShape);

	this->heading = 0;
	this->position = Point2(SWIDTH / 2, SHEIGHT / 2);
}

void Projectile::update(float deltaTime)
{
	circleCollisionShape = Circle(this->position.x, this->position.y, 8);

	cull();
	float angle = heading - PI / 2;
	Vector2 force = Vector2(cos(angle), sin(angle));

	force *= 100 * deltaTime;
	this->position += force * 10000 * deltaTime;

	this->rotation = Point3(this->rotation.x, this->rotation.y, heading);
}

void Projectile::cull() {

	if (position.x > SWIDTH + 16) {
		this->isOutOfScreen = true;
	}

	if (position.x < -16) {
		this->isOutOfScreen = true;
	}

	if (position.y > SHEIGHT + 16) {
		this->isOutOfScreen = true;
	}

	if (position.y < -16) {
		this->isOutOfScreen = true;
	}
}