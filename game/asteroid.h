#ifndef ASTEROID_H
#define ASTEROID_H

#include "entity.h"
#include "vectorx.h"

class Asteroid : public Entity {
public:
	Asteroid();
	virtual void update(float deltaTime);
private:

};
#endif /* ASTEROID_H */