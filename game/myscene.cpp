/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <vector>


#include "myscene.h"

 
MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	playerA = new Player(RGBAColor(255,0,0));
	this->addChild(playerA);
	

	playerB = new Player(RGBAColor(0, 255, 0));
	this->addChild(playerB);
}


MyScene::~MyScene()
{
	delete playerA;
	delete playerB;
}

void MyScene::update(float deltaTime)
{
	playerA->handleInput(1);
	playerB->handleInput(2);

}