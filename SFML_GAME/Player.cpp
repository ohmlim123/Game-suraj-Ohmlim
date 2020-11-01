#include "Player.h"

//Initializer Function
void Player::initVariables()
{

}

void Player::initComponents()
{
	
}


//Contructor / Destructor
Player::Player(float x , float y , sf::Texture& texture_sheet)
{
	this->initVariables();
	

	
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite,0.f,0.f,50.f,53.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent( texture_sheet);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 7, 0, 47,52);
	this->animationComponent->addAnimation("WALK", 10.f, 0, 1, 7, 1, 47, 52);
	
	
	
}

Player::~Player()
{

}

//Functions
void Player::update(const float& dt)
{
	
		this->movementcomponent->update(dt);

		if (this->movementcomponent->getState(IDLE))
			this->animationComponent->play("IDLE", dt);
		else if (this->movementcomponent->getState(MOVING_LEFT))
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
			this->animationComponent->play("WALK", dt);
		}
		else if (this->movementcomponent->getState(MOVING_RIGHT))
		{
			this->sprite.setOrigin(50.f,0.f);
			this->sprite.setScale(-1.f, 1.f);
			this->animationComponent->play("WALK", dt);
		}
		else if (this->movementcomponent->getState(MOVING_UP))
		{
			this->animationComponent->play("WALK", dt);
		}
		else if (this->movementcomponent->getState(MOVING_DOWN))
		{
			this->animationComponent->play("WALK", dt);
		}
		

		this->hitboxComponent->update();
		
}
