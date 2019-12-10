#ifndef WEAPONPICKUP_H
#define WEAPONPICKUP_H

#include "pickup.h"

class WeaponPickup : public Pickup
{
public:
	WeaponPickup();

	void update(float deltaTime);

private:

};

#endif /* WEAPONPICKUP_H */
