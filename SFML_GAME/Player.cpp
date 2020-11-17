#include"stdafx.h"
#include "Player.h"

//Initializer Function
void Player::initVariables()
{
	this->attacking = false;
	this->sprite.setOrigin(115.f, 0.f);
	this->sprite.setScale(-2.f, 2.f);

}

void Player::initComponents()
{

}


//Contructor / Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();



	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 84.f, 30.f, 66.f, 90.f);
	this->createMovementComponent(350.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 0, 0, 84, 66);
	this->animationComponent->addAnimation("WALK", 8.f, 0, 1, 7, 1, 84, 66);
	this->animationComponent->addAnimation("ATTACK", 9.f, 0, 3, 5, 3, 112, 66);


}

Player::~Player()
{

}
//Accessors
AttributeComponent* Player::getAttributeComponent()
{

	return this->attributeComponent;
}
//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{


	this->attributeComponent->gainExp(exp);
}




void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//Set Origuin depending on direction
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(20.f, 0.f);
		}
		else // Facing right
		{
			this->sprite.setOrigin(135.f, 0.f);
		}
		//animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else // Facing right
			{
				this->sprite.setOrigin(115.f, 0.f);
			}
		}

	}
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
}
void Player::update(const float& dt)
{


	this->movementcomponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);



	this->hitboxComponent->update();

}



void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);


	this->hitboxComponent->render(target);
}