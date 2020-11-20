#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	//this->enemySpawner = enemySpawner;
}

void Enemy::initAnimation()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 1, 2, 1 , 65, 84);
	this->animationComponent->addAnimation("WALK_LEFT", 12.f, 0, 0, 2, 0, 65, 84);
	this->animationComponent->addAnimation("WALK_RIGHT", 12.f, 0, 2, 2, 2, 65, 84);
	
}




//Contructor / Destructor
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
	
{
	this->initVariables();



	

	this->createHitboxComponent(this->sprite, 84.f, 30.f, 66.f, 90.f);
	this->createMovementComponent(50.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	


	this->setPosition(x, y);
	this->initAnimation();


}

Enemy::~Enemy()
{

}


void Enemy::updateAnimation(const float& dt)
{
	
	if (this->movementcomponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}

	else if (this->movementcomponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(2.f, 2.f);
		}

		this->animationComponent->play("WALK", dt, this->movementcomponent->getVelocity().x, this->movementcomponent->getMaxVelocity());
	}
	else if (this->movementcomponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(115.f, 0.f);
			this->sprite.setScale(-2.f, 2.f);
		}
		this->animationComponent->play("WALK", dt, this->movementcomponent->getVelocity().x, this->movementcomponent->getMaxVelocity());
	}

	else if (this->movementcomponent->getState(JUMP))
	{
		this->animationComponent->play("JUMP", dt);
	}
}
void Enemy::update(const float& dt)
{


	this->movementcomponent->update(dt);

	//this->updateAttack();

	//this->updateAnimation(dt);



	this->hitboxComponent->update();

}



void Enemy::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);

	
	this->hitboxComponent->render(target);
}