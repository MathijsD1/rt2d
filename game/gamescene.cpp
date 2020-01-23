#include <fstream>
#include <sstream>
#include <vector>
#include "gamescene.h"

GameScene* GameScene::instance = 0;

GameScene::GameScene() : Scene()
{
	// start the timer.
	t.start();

	Reset();
}

void GameScene::Reset() 
{
	int currentPickup = 0;

	for (int i = pickups.size(); i--; )
	{
		Pickup* p = pickups.at(i);

		this->removeChild(p);
		pickups.erase(pickups.begin() + i);
		delete p;
	}

	if (playerA != nullptr) {
		this->removeChild(playerA);
		delete playerA;
	}

	if (playerB != nullptr) {
		this->removeChild(playerB);
		delete playerB;
	}

	//Create Player A.
	playerA = new Player(RGBAColor(0, 255, 255));

	//Add Player A to the Scene.
	this->addChild(playerA);

	//Create Player B.
	playerB = new Player(RGBAColor(255, 255, 0));

	//Add Player B to the Scene.
	this->addChild(playerB);
}


GameScene::~GameScene()
{
	delete playerA;
	delete playerB;
}

void GameScene::update(float deltaTime)
{
	if (input()->getKey(KeyCode::Enter)) {
		Reset();
	}

	updatePickups(deltaTime);
	updateProjectiles();

	//// Players

	if (playerA->isAlive()) 
	{
		//Input with WASD for Player A.
		playerA->handleInput(1);
	}
	else {
		Reset();
	}

	if (playerB->isAlive())
	{
		//Input with WASD for Player A.
		playerB->handleInput(2);
	}
	else {
		Reset();
	}
}

void GameScene::updatePickups(float deltaTime)
{
	if (pickups.size() < pickupLimit) {
		pickupSpawnDelay -= deltaTime;
	}

	if (pickupSpawnDelay < 0) 
	{
		if (pickups.size() < pickupLimit)
		{
			int randomPickupValue = Random().getRandomBetween(0, 1);

			if (randomPickupValue == 0) {
				Pickup* pickup = new WeaponPickup();
				this->addChild(pickup);

				pickups.push_back(pickup);
			}

			if (randomPickupValue == 1) {
				Pickup* pickup = new HealthPickup();
				this->addChild(pickup);

				pickups.push_back(pickup);
			}

			pickupSpawnDelay = pickupDefaultDelay;
		}
	}

	//Pickup collision detection

	int currentPickup = 0;
	for (auto x : pickups)
	{
		x->updateCollider();

		//Player collision detection with Pickups.
		if (Collider::circle2circle(playerA->circleCollisionShape, x->circleCollisionShape)) {
			
			Pickup* p = (Pickup*)x;

			//Activate the pickup
			p->use(playerA);

			//Remove the pickup from the scene
			this->removeChild(p);

			//Remove it from the vector
			pickups.erase(pickups.begin() + currentPickup);

			//Deconstruct
			delete p;
		}

		if (Collider::circle2circle(playerB->circleCollisionShape, x->circleCollisionShape)) {

			Pickup* p = (Pickup*)x;

			//Activate the pickup
			p->use(playerB);

			//Remove the pickup from the scene
			this->removeChild(p);

			//Remove it from the vector
			pickups.erase(pickups.begin() + currentPickup);

			//Deconstruct
			delete p;
		}

		currentPickup++;
	}

	currentPickup = pickups.size();
}

void GameScene::updateProjectiles() 
{
	/*
	int currentProjectile = 0;
	for (auto x : projectiles) 
	{
		if (x->isOutOfScreen) {
			Projectile* p = (Projectile*)x;

			this->removeChild(p);
			projectiles.erase(projectiles.begin() + currentProjectile);
			delete p;
		}

		currentProjectile++;
	}*/

	for (int i = projectiles.size(); i--; )
	{
		Projectile* p = projectiles.at(i);

		for (int i = pickups.size(); i--;)
		{
			Pickup* pu = pickups.at(i);

			if (Collider::circle2circle(p->circleCollisionShape, pu->circleCollisionShape)) 
			{
				//Remove the pickup from the scene
				this->removeChild(pu);

				//Remove it from the vector
				pickups.erase(pickups.begin() + i);

				//Deconstruct
				delete pu;
			}
		}


		if (Collider::circle2circle(playerB->circleCollisionShape, p->circleCollisionShape) && p->sprite()->color != playerB->sprite()->color)
		{
			playerB->damage(10);

			this->removeChild(p);
			projectiles.erase(projectiles.begin() + i);
			delete p;
			break;
		}

		if (Collider::circle2circle(playerA->circleCollisionShape, p->circleCollisionShape) && p->sprite()->color != playerA->sprite()->color)
		{
			playerA->damage(10);

			this->removeChild(p);
			projectiles.erase(projectiles.begin() + i);
			delete p;
			break;
		}

		if (p->isOutOfScreen) {
			this->removeChild(p);
			projectiles.erase(projectiles.begin() + i);
			delete p;
		}
	}
}

void GameScene::addProjectileToList(Projectile* p) 
{
	projectiles.push_back(p);
}

GameScene* GameScene::getInstance() 
{
	if (GameScene::instance == 0) 
	{
		GameScene::instance = new GameScene();
	}

	return instance;
}

