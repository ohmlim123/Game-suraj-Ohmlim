#ifndef ENTITY_H
#define ENTITY_H

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"AttributeComponent.h"
#include"SkillComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;

class Entity
{
private:
	void iniVarialbe();

protected:
	
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementcomponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;

public:

	Entity();
	virtual ~Entity();

	//Componet Function
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x,float offset_y,
		float width,float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent( sf::Texture& texture_sheet);
	void createAttributeComponent(const	unsigned level);
	void createSkillComponent();
	
	//Accessors


	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	
	//Modifier
	virtual void setPosition(const float x, const float y);

	//Function

	virtual void move(const float x, const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();


	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};
#endif
