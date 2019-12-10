#include <fstream>
#include <sstream>
#include <vector>


#include "myscene.h"

float delay = 0.1f;

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
	delay -= deltaTime;

	if (delay < 0) 
	{
		if (pickups.size() < 8)
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

			delay = 0.1f;
		}
	}
}


