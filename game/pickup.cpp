#include "pickup.h"

float scaleAmount = 1.6f;

Pickup::Pickup() 
{
	this->addSprite("assets/pickup_base.tga");
	this->sprite()->color = RGBAColor(0, 255, 0);
	this->sprite()->filter(0);
	
	this->position = Vector2(Random().getRandomBetween(0, SWIDTH), Random().getRandomBetween(0, SHEIGHT));
}

void Pickup::update(float deltaTime)
{
	if (this->scale.x < scaleAmount)
	{
		this->scale = this->scale += deltaTime;
	}
}