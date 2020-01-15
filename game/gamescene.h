#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <rt2d/scene.h>
#include "pickups.h"
#include "collider.h"
#include "canvas.h"
#include "asteroid.h"
#include "player.h"
#include "projectile.h"


/// @brief The GameScene class is the Scene implementation.
class GameScene : public Scene
{
public:

	static GameScene* getInstance();
	/// @brief Destructor
	virtual ~GameScene();

	void updatePickups(float deltaTime);
	void updateProjectiles();
	void addProjectileToList(Projectile* p);

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/// @brief Constructor
	GameScene();

	static GameScene* instance;

	Player* playerA;
	Player* playerB;

	Asteroid* asteroidA;

	int pickupLimit = 8;

	float pickupSpawnDelay = 0.3f;
	float pickupDefaultDelay = 0.3f;

	std::vector<Pickup*> pickups;
	std::vector<Projectile*> projectiles;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;

};

#endif /* GAMESCENE_H */