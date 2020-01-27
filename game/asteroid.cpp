#include "asteroid.h"

Asteroid::Asteroid() : Entity() 
{
	randomScale = Random().getRandomBetween(2, 4);

	this->addSprite("assets/asteroid.tga");
	this->sprite()->color = WHITE;
	this->sprite()->filter(0);
	this->scale = Point3(randomScale, randomScale);

	collisionShape = new Shape();
	collisionShape->position = this->position;

	Line c1;
	c1.color = this->sprite()->color;
	c1.color.a = 0;
	c1.createCircle(14, 100);
	collisionShape->addLine(&c1);
	this->addChild(collisionShape);

	this->pos = this->position;

	this->heading = Random().getRandomBetween(0, 360);
	this->rotation = Point3(this->rotation.x, this->rotation.y, Random().getRandomBetween(0, 360));
}

void Asteroid::update(float deltaTime) 
{
	this->rotation = Point3(this->rotation.x, this->rotation.y, this->rotation.z += 3 * deltaTime);

	circleCollisionShape = Circle(this->position.x, this->position.y, (randomScale * 9));

	wrapEdges();

	float angle = heading - PI / 2;
	Vector2 force = Vector2(cos(angle), sin(angle));

	force *= (500 / randomScale)  * deltaTime;
	this->pos += force;

	this->position = pos;

}

void Asteroid::wrapEdges() {
	float buffer = 16 * 2;

	if (pos.x > SWIDTH + buffer) {
		pos.x = -buffer;
	}

	if (pos.x < -buffer) {
		pos.x = SWIDTH + buffer;
	}

	if (pos.y > SHEIGHT + buffer) {
		pos.y = -buffer;
	}

	if (pos.y < -buffer) {
		pos.y = SHEIGHT + buffer;
	}
}
