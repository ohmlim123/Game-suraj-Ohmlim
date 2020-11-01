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

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent( texture_sheet);

	this->animationComponent->addAnimation("IDLE_WAIT", 10.f, 0, 0, 7, 0, 47,52);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 7, 1, 47, 52);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 4, 7, 4, 47, 52);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 7, 7, 7, 47, 52);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 3, 7, 3, 47, 52);
	
	
}

Player::~Player()
{

}

//Functions
void Player::update(const float& dt)
{
	
		this->movementcomponent->update(dt);

		if (this->movementcomponent->getState(IDLE))
			this->animationComponent->play("IDLE_WAIT", dt);
		else if(this->movementcomponent->getState(MOVING_LEFT))
			this->animationComponent->play("WALK_LEFT", dt);
		else if (this->movementcomponent->getState(MOVING_RIGHT))
			this->animationComponent->play("WALK_RIGHT", dt);
		else if (this->movementcomponent->getState(MOVING_UP))
			this->animationComponent->play("WALK_UP", dt);
		else if (this->movementcomponent->getState(MOVING_DOWN))
			this->animationComponent->play("WALK_DOWN", dt);
		
}
