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

	spaceship = new Spaceship(Point(SWIDTH / 2, SHEIGHT / 2));

	this->addChild(spaceship);
}


MyScene::~MyScene()
{
	delete spaceship;
}

void MyScene::update(float deltaTime)
{
	if (t.seconds() > 0.0333f) {
		RGBAColor color = spaceship->sprite()->color;
		spaceship->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
}
