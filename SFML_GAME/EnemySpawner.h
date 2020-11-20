#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H
#include"Tile.h"

class Tile;

class EnemySpawner
	: public Tile
{
private:
	
	

	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDistance;

	


public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, 
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		float grid_size,int enemy_type,int enemy_amount,int enemy_time_to_spawn,float enemy_max_distance);

	virtual ~EnemySpawner();

	//functions
	

	void update();
	void render(sf::RenderTarget& target);
};
#endif
