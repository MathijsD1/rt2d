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

void WeaponPickup::use(Player* p) {

	//If the player already has a weapon then destroy it.
	p->removeWeapon();

	//Give the player a new weapon!
	p->addWeapon(new AutoCannon());

	std::cout << "WEAPON PICKUP USE ON PLAYER INSTANCE: " << p  << std::endl;
}