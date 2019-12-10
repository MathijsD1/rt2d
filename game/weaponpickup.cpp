#include "weaponpickup.h"

WeaponPickup::WeaponPickup()
{
	this->addSprite("assets/pickup_weapon.tga");
	this->sprite()->color = RGBAColor(255, 0, 0);
	this->sprite()->filter(0);

	float scale = 1;
	this->scale = Point3(scale, scale, scale);

	this->position = Vector2(Random().getRandomBetween(0, SWIDTH), Random().getRandomBetween(0, SHEIGHT));

	std::cout << "Created new Weapon Pickup instance! " << std::endl;
}

void WeaponPickup::update(float deltaTime)
{

}