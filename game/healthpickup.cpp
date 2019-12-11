#include "healthpickup.h"

HealthPickup::HealthPickup() : Pickup()
{
	this->addSprite("assets/pickup_health.tga");
	this->sprite()->color = RGBAColor(0, 255, 0);
	this->sprite()->filter(0);

	std::cout << "Created new Health Pickup instance! " << std::endl;
}

void HealthPickup::update(float deltaTime)
{

}