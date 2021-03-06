#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, 
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	:Tile(grid_x, grid_y, gridSizeF, texture, texture_rect, false, TileTypes::ENEMYSPAWNER)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
}

EnemySpawner::~EnemySpawner()
{

}
//functions



void EnemySpawner::update()
{

}

void EnemySpawner::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
