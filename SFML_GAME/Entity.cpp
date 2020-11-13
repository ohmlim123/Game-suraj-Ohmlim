#include"stdafx.h"
#include"Entity.h"
void Entity::iniVarialbe()
{
	this->hitboxComponent = NULL;
	this->movementcomponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	this->skillComponent = NULL;
}
Entity::Entity()
{
	this->iniVarialbe();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementcomponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillComponent;
}

//Component Function
void Entity::setTexture(sf::Texture& texture)
{
	
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y,width,height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementcomponent = new MovementComponent(this->sprite, maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent( sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent()
{

}



const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();


	return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
			);


	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementcomponent)
		return this->hitboxComponent->getnextPosition(this->movementcomponent->getVelocity() * dt);

	
	return sf::FloatRect(-1.f,-1.f,-1.f,-1.f);
}



// Functions

void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x,y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt )
{
	if (this->movementcomponent)
	this->movementcomponent->move(dir_x, dir_y,dt); // Set Velocity
	
	
}

void Entity::stopVelocity()
{
	if (this->movementcomponent)
		this->movementcomponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementcomponent)
		this->movementcomponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementcomponent)
		this->movementcomponent->stopVelocityY();
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget& target)
{
	

}


