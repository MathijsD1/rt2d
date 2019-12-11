#ifndef HEALTHPICKUP_H
#define HEALTHPICKUP_H

#include "pickup.h"

class HealthPickup : public Pickup
{
public:
	HealthPickup();

	void update(float deltaTime);

	virtual void use(Player* p);

private:

	float healAmount = 20;
};

#endif /* HEALTHPICKUP_H */
