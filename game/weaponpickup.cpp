#include "weaponpickup.h"

WeaponPickup::WeaponPickup() : Pickup()
{
	this->addSprite("assets/pickup_weapon.tga");
	this->sprite()->color = RGBAColor(255, 0, 0);
	this->sprite()->filter(0);

	std::cout << "Created new Weapon Pickup instance! " << std::endl;
}

void WeaponPickup::update(float deltaTime)
{

}