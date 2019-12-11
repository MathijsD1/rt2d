#include <fstream>
#include <sstream>
#include <vector>

#include "myscene.h"

MyScene::MyScene() : Scene()
{

	// start the timer.
	t.start();

	//Create Player A.
	playerA = new Player(RGBAColor(255,0,0));

	//Add Player A to the Scene.
	this->addChild(playerA);

	//Create Player B.
	playerB = new Player(RGBAColor(0, 255, 0));

	//Add Player B to the Scene.
	this->addChild(playerB);
}


MyScene::~MyScene()
{
	delete playerA;
	delete playerB;
}

void MyScene::update(float deltaTime)
{
	updatePickups(deltaTime);

	//Input with WASD for Player A.
	playerA->handleInput(1);

	//Input with NUM Keys for Player B.
	playerB->handleInput(2);
}

void MyScene::updatePickups(float deltaTime) 
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
	for (auto&& x : pickups)
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


