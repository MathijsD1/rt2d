#include "asteroid.h"

Asteroid::Asteroid() : Entity() 
{
	this->addSprite("assets/asteroid.tga");
	this->sprite()->color = WHITE;
	this->sprite()->filter(0);
	this->scale = Point3(2,2);
}

void Asteroid::update(float deltaTime) {

}