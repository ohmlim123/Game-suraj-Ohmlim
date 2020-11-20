#ifndef ENEMY_H
#define ENEMY_H

#include"Entity.h"
#include"EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy :
	public Entity
{
private:
	//Variables
	//EnemySpawner& enemySpawner;


	//Initlizer fuction

	void initVariables();
	void initAnimation();

public:
	Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();

	//function
	void updateAnimation(const float& dt);

	void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};
#endif //enemy
