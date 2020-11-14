#include"stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite , 
	float maxVelocity, float acceleration , float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->gravity = 100.f;
}

MovementComponent::~MovementComponent()
{

}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}


//Function




const bool MovementComponent::getState(const short unsigned state) const
{
	int row = 0;
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		{
			row = 0;
			return true;
		}
			

		
		break;

	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		
		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
		{
			row = 1;
			return true;
		}
			

		

		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
		{
			row = 4;
			return true;
		}
			

		

		break;

	}

	return false;
}

void MovementComponent::stopVelocity()
{
	//Reset the velocity to 0
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	//Reset the velocity x to 0

	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	//Reset the velocity y to 0

	this->velocity.y = 0.f;
}

void MovementComponent::updategravity()
{
	this->velocity.y += gravity;
}

void MovementComponent::jump(float jump_high)
{
	this->velocity.y -= jump_high;
}

void MovementComponent::bounce(const float dir_x, const float dir_y, const float x_force, const float y_force, const float& dt)
{
	this->velocity.x += x_force * dir_x;
	this->velocity.y += y_force * dir_y;
}

const float MovementComponent::get_gravity()
{
	return this->gravity;
}

void MovementComponent::set_gravity(float gravitate)
{
	this->gravity = gravitate;
}








void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	

	//Accelation

	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;


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
		this->velocity.x -= deceleration * dt ;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
		

	}
	else if(this->velocity.x < 0.f) // Check for negative x
	{
		//Max velocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration x negetive
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	if (this->velocity.y > 0.f)//Check for positive y
	{
		//Max Velocity check positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;


		//Deceleration y positive
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;


	}
	else if (this->velocity.y < 0.f) // Check for negative y
	{
		//Max velocity check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration y negetive
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Gravity
	this->updategravity();

	//Final move
	this->sprite.move(this->velocity * dt); // Use velocity

	

}
