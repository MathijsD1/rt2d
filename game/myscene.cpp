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
	//Input with WASD for Player A.
	playerA->handleInput(1);

	//Input with NUM Keys for Player B.
	playerB->handleInput(2);
}