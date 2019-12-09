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

	Pickup* pickup = new Pickup();
	this->addChild(pickup);
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
		Pickup* pickup = new Pickup();
		this->addChild(pickup);

		delay = 0.1f;
	}
}


