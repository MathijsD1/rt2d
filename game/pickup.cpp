#include "pickup.h"

float scaleAmount = 1.6f;

Pickup::Pickup() : Entity()
{	
	this->position = Vector2(Random().getRandomBetween(0, SWIDTH), Random().getRandomBetween(0, SHEIGHT));

	std::cout << "Created new pickup!" << std::endl;
}

void Pickup::update(float deltaTime) {

}

void Pickup::updateCollider()
{
	circleCollisionShape = Circle(this->position.x, this->position.y, collisionSpan);
}