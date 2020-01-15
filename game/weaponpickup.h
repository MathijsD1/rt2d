#ifndef WEAPONPICKUP_H
#define WEAPONPICKUP_H

#include "pickup.h"
#include "autocannon.h"

class WeaponPickup : public Pickup
{
public:
	WeaponPickup();

	void update(float deltaTime);
	virtual void use(Player* p);

private:

};

#endif /* WEAPONPICKUP_H */
