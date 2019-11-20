/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
 
MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	arenaBoidA = new ArenaBoid(RGBAColor(255,0,0));
	this->addChild(arenaBoidA);

	arenaBoidB = new ArenaBoid(RGBAColor(0, 255, 0));
	this->addChild(arenaBoidB);
}


MyScene::~MyScene()
{
	delete arenaBoidA;
	delete arenaBoidB;
}

void MyScene::update(float deltaTime)
{
	arenaBoidA->handleInput(1);
	arenaBoidB->handleInput(2);
}