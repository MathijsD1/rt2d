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
	for (int i = pickups.size(); i--; )
	{
		Pickup* p = pickups.at(i);

		this->removeChild(p);
		pickups.erase(pickups.begin() + i);
		delete p;
	}

	for (int i = projectiles.size(); i--; )
	{
		Projectile* p = projectiles.at(i);

		this->removeChild(p);
		projectiles.erase(projectiles.begin() + i);
		delete p;
	}

	for (int i = asteroids.size(); i--; )
	{
		Asteroid* p = asteroids.at(i);

		this->removeChild(p);
		asteroids.erase(asteroids.begin() + i);
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

	if (playerAText != nullptr) {
		this->removeChild(playerAText);
		delete playerAText;
	}

	if (playerBText != nullptr) {
		this->removeChild(playerBText);
		delete playerBText;
	}

	//Create Player A.
	playerA = new Player(RGBAColor(0, 255, 255));

	//Add Player A to the Scene.
	this->addChild(playerA);

	//Create Player B.
	playerB = new Player(RGBAColor(255, 255, 0));

	//Add Player B to the Scene.
	this->addChild(playerB);

	playerAText = new Text();
	this->addChild(playerAText);
	playerAText->scale = Point2(0.3f, 0.3f);


	playerBText = new Text();
	this->addChild(playerBText);
	playerBText->scale = Point2(0.3f, 0.3f);

}


GameScene::~GameScene()
{
	delete playerA;
	delete playerB;

	delete playerAText;
	delete playerBText;
}

void GameScene::update(float deltaTime)
{
	if (input()->getKeyDown(KeyCode::Enter)) {
		Reset();
	}

	//std::cout << "Player A Health: " << playerA->getHealth() << " Player B Health: " << playerB->getHealth() << std::endl;

	updatePickups(deltaTime);
	updateProjectiles();
	updateAsteroids(deltaTime);

	//// Players

	if (playerA->isAlive()) 
	{
		//Input with WASD for Player A.
		playerA->handleInput(1);
		playerAText->message("Health: " + std::to_string(playerA->getHealth()), playerA->sprite()->color);
		
	}
	else {
		playerAText->message("You lost! Press Enter to restart!", RED);
		playerBText->message("You won! Press Enter to restart!", GREEN);
	}

	if (playerB->isAlive())
	{
		//Input with WASD for Player A.
		playerB->handleInput(2);
		playerBText->message("Health: " + std::to_string(playerB->getHealth()), playerB->sprite()->color);
	}
	else {
		playerAText->message("You won! Press Enter to restart!", GREEN);
		playerBText->message("You lost! Press Enter to restart!", RED);
	}

	playerBText->position = Point2(playerB->position.x, playerB->position.y + -50);
	playerAText->position = Point2(playerA->position.x, playerA->position.y + -50);
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
	for (int i = projectiles.size(); i--; )
	{
		Projectile* p = projectiles.at(i);

		for (int b = pickups.size(); b--;)
		{
			Pickup* pu = pickups.at(b);

			if (Collider::circle2circle(p->circleCollisionShape, pu->circleCollisionShape)) 
			{
				//Remove the pickup from the scene
				this->removeChild(pu);

				//Remove it from the vector
				pickups.erase(pickups.begin() + b);

				//Deconstruct
				delete pu;
			}
		}

		for (int y = asteroids.size(); y--;)
		{
			Asteroid* as = asteroids.at(y);

			if (Collider::circle2circle(p->circleCollisionShape, as->circleCollisionShape))
			{
				//Remove the pickup from the scene
				this->removeChild(as);

				//Remove it from the vector
				asteroids.erase(asteroids.begin() + y);

				//Deconstruct
				delete as;
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

void GameScene::updateAsteroids(float deltaTime) 
{
	asteroidSpawnDelay -= deltaTime;

	if (asteroidSpawnDelay <= 0) {
		Asteroid* asst = new Asteroid();
		asteroids.push_back(asst);
		asst->position = Vector2(0, Random().getRandomBetween(0, 0));
		this->addChild(asst);
		asteroidSpawnDelay = 1;
	}

	for (int i = asteroids.size();i--;)
	{
		Asteroid* asteroid = asteroids.at(i);

		if (Collider::circle2circle(asteroid->circleCollisionShape, playerA->circleCollisionShape)) 
		{
			playerA->damage(15 * asteroid->scale.x);

			this->removeChild(asteroid);
			asteroids.erase(asteroids.begin() + i);
			delete asteroid;
			break;
		}

		if (Collider::circle2circle(asteroid->circleCollisionShape, playerB->circleCollisionShape))
		{
			playerB->damage(15 * asteroid->scale.x);

			this->removeChild(asteroid);
			asteroids.erase(asteroids.begin() + i);
			delete asteroid;
			break;
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

