#ifndef AUTOCANNON_H
#define AUTOCANNON_H

#include "weapon.h"

class AutoCannon : public Weapon
{
public:
	AutoCannon();
	virtual void update(float deltaTime);
};

#endif /* AUTOCANNON_H */