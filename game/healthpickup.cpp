#include "healthpickup.h"

HealthPickup::HealthPickup()
{
	this->addSprite("assets/pickup_health.tga");
	this->sprite()->color = RGBAColor(0, 255, 0);
	this->sprite()->filter(0);

	this->position = Vector2(Random().getRandomBetween(0, SWIDTH), Random().getRandomBetween(0, SHEIGHT));

	std::cout << "Created new Weapon Pickup instance! " << std::endl;
}

void HealthPickup::update(float deltaTime)
{

}