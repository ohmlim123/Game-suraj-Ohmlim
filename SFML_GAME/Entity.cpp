#include"stdafx.h"
#include"Entity.h"
void Entity::iniVarialbe()
{
	this->hitboxComponent = NULL;
	this->movementcomponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	this->skillComponent = NULL;
	this->Can_jump = false;

	this->jump_height = 500.f;
	//this->bounce_distance = 100.f;

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

void Entity::speedup()
{
	if (this->movementcomponent)
		this->movementcomponent->speedup();
}

void Entity::speeddown()
{
	if (this->movementcomponent)
		this->movementcomponent->speeddown();
}

void Entity::stopVelocityY()
{
	if (this->movementcomponent)
		this->movementcomponent->stopVelocityY();
}

const bool Entity::get_can_jump()
{
	return this->Can_jump;
}

void Entity::set_can_jump(bool Getcanjump)
{
	this->Can_jump = Getcanjump;
}

const float Entity::get_jump_height() const
{
	return this->jump_height;
}

const float Entity::get_gravity()
{
	return this->movementcomponent->get_gravity();
}

void Entity::set_gravity(float gravitate)
{
	this->movementcomponent->set_gravity(gravitate);
}



void Entity::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Entity::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Entity::jump(float jump_height)
{
	if (this->movementcomponent)
	{
		this->movementcomponent->jump(jump_height);
	}
}

void Entity::bounce(const float dir_x, const float dir_y, const float x_force, const float y_force, const float& dt)
{
	if (this->movementcomponent) {
		this->movementcomponent->bounce(dir_x, dir_y, x_force, y_force, dt);
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget& target)
{
	

}


