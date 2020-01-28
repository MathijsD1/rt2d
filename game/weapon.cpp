#include "weapon.h"
#include "projectile.h"
#include "gamescene.h"

Weapon::Weapon() : Entity()
{

}

void Weapon::update(float deltaTime) 
{
	fireRate -= deltaTime * 3;
}

void Weapon::fire(float dir, Vector2 firePos, RGBAColor projectileColor) {
	if (fireRate < 0) 
	{
		Projectile* p = new Projectile;
		p->position = firePos;
		p->sprite()->color = projectileColor;

		p->heading = dir + Random().getRandomFloatBetween(-0.1f, 0.1f);	

		GameScene::getInstance()->addChild(p);
		GameScene::getInstance()->addProjectileToList(p);

		ammo--;
		fireRate = 1;
	}
}