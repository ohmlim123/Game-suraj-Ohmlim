#include"stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite),textureSheet(texture_sheet),lastAnimation(NULL),priorityAnimaiton(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}





//Accessor
const bool& AnimationComponent::isDone(const std::string key) 
{
	
		return this->animations[key]->isDone() ;
}

//Function

void AnimationComponent::addAnimation(
	std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int  width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}
const bool& AnimationComponent::play(std::string key, const float& dt, const bool priority )
{
	
	if (this->priorityAnimaiton)// If there is prioity animation
	{
		if (this->priorityAnimaiton == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			//If the priority anmation is done ,remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimaiton = NULL;
			}
		}
	}
	else // Play animation of no other priority animation
	{
		if (priority)
		{
			this->priorityAnimaiton = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}
const bool& AnimationComponent::play(std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority )
{
	if (this->priorityAnimaiton)// If there is prioity animation
	{
		if (this->priorityAnimaiton == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority anmation is done ,remove it
			if (this->animations[key]->play(dt , abs(modifier / modifier_max)))
			{
				this->priorityAnimaiton = NULL;
			}
		}
	}
	else // Play animation of no other priority animation
	{
		if (priority)
		{
			this->priorityAnimaiton = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}
	return this->animations[key]->isDone();
}	

