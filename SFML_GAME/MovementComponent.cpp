#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite , 
	float maxVelocity, float acceleration , float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}


//Function

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	

	//Accelation

	this->velocity.x += this->acceleration * dir_x;

	if (this->velocity.x > 0.f)// Check for right
	{
		
	}
	else if (this->velocity.x < 0.f) // Check for left
	{
		if (this->velocity.x > -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
	}

	this->velocity.y += this->acceleration * dir_y;

}

void MovementComponent::update(const float& dt)
{
	//Deceleration the sprite and check controls the maxinmun veloctiy Moves the sprite
	if (this->velocity.x > 0.f)//Check for positive x
	{
		//Max Velocity check positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		
		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
		

	}
	else if(this->velocity.x < 0.f) // Check for negative x
	{
		//Max velocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration x negetive
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	if (this->velocity.y > 0.f)//Check for positive y
	{
		//Max Velocity check positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;


		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;


	}
	else if (this->velocity.y < 0.f) // Check for negative y
	{
		//Max velocity check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration y negetive
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(this->velocity * dt); // Use velocity

}
