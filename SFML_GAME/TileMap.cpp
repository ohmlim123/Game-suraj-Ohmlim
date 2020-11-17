#include"stdafx.h"
#include "TileMap.h"
#include"MovementComponent.h"

void TileMap::clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}

	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<std::vector<Tile*> > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP:FAIL TO LOAD TEXTURESHEET :: FILENAME" << texture_file << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineColor(sf::Color::Transparent);
	//this->collisionBox.setOutlineThickness(0.f);
}

TileMap::TileMap(const std::string file_name)
{
	

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_name);


	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineColor(sf::Color::Transparent);
	//this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

//Accessors

const bool  TileMap::TileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{

		return this->map[x][y][z].empty();

	}
	
	return false;
	
}

const sf::Texture* TileMap::getTileSheet() const
{

	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int z) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < this->map[x].size())
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return static_cast<int>(this->map[x][y][layer].size());
			}
		}
	}
	
	return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return this->maxSizeWorldGrid;
}
const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeWorldF;
}

//Functions

void TileMap::addTile(const int  x, const  int y ,const int z,const sf::IntRect& texture_rect,const bool& collision,const short& type)
{

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		
			/*OK TO add TILE*/
			this->map[x][y][z].push_back (new Tile(x , y , this->gridSizeF,this->tileSheet,texture_rect,collision,type));
			std::cout << "DEBUG for create Tile!! \n";
		
	}
}

void TileMap::removeTile(const int  x, const  int y, const int z)
{

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			/*OK TO remove TILE*/
			delete this->map[x][y][z][map[x][y][z].size() - 1] ;
			this->map[x][y][z].pop_back();
			std::cout << "DEBUG for remove Tile!!  \n";
		}

	}
	

}

void TileMap::saveToFile(const std::string file_name)
{
	/*Save the entire tile map to a text-file 
	Format:
	Basic :
	Size x y
	gridSize
	layers
	texture file

	All tiles:
	gridPos  x y layer , T
	exture rect x y , 
	collision ,type
	*/

	std::ofstream out_file;

	out_file.open(file_name);
	
	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString() << " ";
							// MAKE SURE THIS LAST SPACE IS NOT SAVED!!
						}
						
					}
				}
			}
		}
			
	}
	else
	{
		std::cout << "ERROR:: RILE MAP COUL DNOT T OSAVE FILE " << file_name << "\n";
	}

	out_file.close();


}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{

		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string  texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<std::vector<Tile*> > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());
				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP:FAIL TO LOAD TEXTURESHEET :: FILENAME" << texture_file << "\n";

		//LOAT ALL TILES

		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
				this->map[x][y][z].push_back ( 
					new Tile(
					x, y, 
					this->gridSizeF, 
					this->tileSheet, 
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI) ,
					collision,
					type
				)
			);
		}

	}
	else
	{
		std::cout << "ERROR:: RILE MAP COULD NOT LOAD FROM  " << file_name << "\n";
	}

	in_file.close();
}

void TileMap::updateCollision(Entity* entity , const float& dt)
{

	//WORLD BOUND

	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
		
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
		

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
		
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
		

	//TILES

	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x ;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x ;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;
	
	

	for (int x = fromX; x < this->toX; x++)
	{
		for (int y = fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{

			
					sf::FloatRect playerBounds = entity->getGlobalBounds();
					sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
					sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

					if (this->map[x][y][this->layer][k]->getCollision() &&
						this->map[x][y][this->layer][k]->intersects(nextPositionBounds))
					{

						switch (this->map[x][y][this->layer][k]->getType())
						{
						case TileTypes::DEFAULT:
							this->update_normal_tile(dt, entity, playerBounds, wallBounds);
							break;
						case TileTypes::JUMP_HIGH:
							this->update_jump_high_tile(dt, entity, playerBounds, wallBounds);
							break;
						case TileTypes::JUMP_LOW:
							this->update_jump_low_tile(dt, entity, playerBounds, wallBounds);
							break;
						case TileTypes::DAMAGING:
							this->update_attack_tile(dt, entity, playerBounds, wallBounds);
							break;
						}
				    }
					
			}

		}
	}



}

void TileMap::update_normal_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds)
{
	//Bottom Collision
	if (playerBounds.top < wallBounds.top
		&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{
		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
		
		entity->set_can_jump(true);
		


	}

	//Walk Space


	//Top collision
	else if (playerBounds.top > wallBounds.top
		&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{

		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);

	}

	//Right collision
	if (playerBounds.left < wallBounds.left
		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

	}

	//Left collision
	else if (playerBounds.left > wallBounds.left
		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
	}
}

void TileMap::update_attack_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds)
{
	//Bottom Collision
	if (playerBounds.top < wallBounds.top
		&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{
		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
		entity->loseHP(1);
	}

	//Walk Space


	//Top collision
	else if (playerBounds.top > wallBounds.top
		&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{

		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
		entity->loseHP(1);
		


	}

	//Right collision
	if (playerBounds.left < wallBounds.left
		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

		entity->loseHP(1);
		

	}

	//Left collision
	else if (playerBounds.left > wallBounds.left
		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
		
		
		entity->loseHP(1);
		
	}
}

void TileMap::update_jump_high_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds)
{
	//Bottom Collision
	if (playerBounds.top < wallBounds.top
		&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{
		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
		entity->bounce(0.f, -1.f, 0.f, entity->get_jump_height() * 3.f, dt);
		entity->set_can_jump(false);
		



	}

	//Top collision
	else if (playerBounds.top > wallBounds.top
		&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{

		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);

	}

	//Right collision
	if (playerBounds.left < wallBounds.left
		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

	}

	//Left collision
	else if (playerBounds.left > wallBounds.left
		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
	}

}

void TileMap::update_jump_low_tile(const float& dt, Entity* entity, sf::FloatRect playerBounds, sf::FloatRect wallBounds)
{
	//Bottom Collision
	if (playerBounds.top < wallBounds.top
		&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{
		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
		entity->bounce(0.f, -1.f, 0.f, entity->get_jump_height() * 1.3f, dt);
		entity->set_can_jump(false);



	}

	//Top collision
	else if (playerBounds.top > wallBounds.top
		&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
		&& playerBounds.left <  wallBounds.left + wallBounds.width - 1
		&& playerBounds.left + playerBounds.width > wallBounds.left + 1
		)
	{

		entity->stopVelocityY();
		entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);

	}

	//Right collision
	if (playerBounds.left < wallBounds.left
		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

	}

	//Left collision
	else if (playerBounds.left > wallBounds.left
		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
		&& playerBounds.top <  wallBounds.top + wallBounds.height - 1
		&& playerBounds.top + playerBounds.height > wallBounds.top + 1
		)
	{
		entity->stopVelocityX();
		entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target,const sf::Vector2i& gridPosition)
{
	

		this->layer = 0;

		this->fromX = gridPosition.x - 6;
		//this->fromX = gridPosition.x - 4;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldGrid.x)
			this->fromX = this->maxSizeWorldGrid.x;

		//this->toX = gridPosition.x + 5;
		this->toX = gridPosition.x + 8;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldGrid.x)
			this->toX = this->maxSizeWorldGrid.x;

		//this->fromY = gridPosition.y - 3;
		this->fromY = gridPosition.y - 6;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldGrid.y)
			this->fromY = this->maxSizeWorldGrid.y;

		//this->toY = gridPosition.y + 5;
		this->toY = gridPosition.y + 8 ;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldGrid.y)
			this->toY = this->maxSizeWorldGrid.y;

		//Invisible Block

		for (int x = fromX; x < this->toX; x++)
		{
			for (int y = fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
					{
						this->defferedRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						this->map[x][y][this->layer][k]->render(target);
					}
					
					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}
				

			}
		}

		//JumpHigh Block
		for (int x = fromX; x < this->toX; x++)
		{
			for (int y = fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == TileTypes::JUMP_HIGH)
					{
						this->defferedRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						this->map[x][y][this->layer][k]->render(target);
					}

					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}


			}
		}

		//JumpLow Block
		for (int x = fromX; x < this->toX; x++)
		{
			for (int y = fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == TileTypes::JUMP_LOW)
					{
						this->defferedRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						this->map[x][y][this->layer][k]->render(target);
					}

					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}


			}
		}
	
	
	



	
}

void TileMap::renderDefferred(sf::RenderTarget& target)
{
	while (!defferedRenderStack.empty())
	{
		defferedRenderStack.top()->render(target);
		defferedRenderStack.pop();
	}
}


