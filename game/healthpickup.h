#ifndef HEALTHPICKUP_H
#define HEALTHPICKUP_H

#include "pickup.h"

class HealthPickup : public Pickup
{
public:
	HealthPickup();

	void update(float deltaTime);

private:

};

#endif /* HEALTHPICKUP_H */
