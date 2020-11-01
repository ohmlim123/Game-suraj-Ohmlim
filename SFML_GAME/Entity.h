#ifndef ENTITY_H
#define ENTITY_H

#include"MovementComponent.h"
#include"AnimationComponent.h"

class Entity
{
private:
	void iniVarialbe();

protected:
	
	sf::Sprite sprite;

	
	MovementComponent* movementcomponent;
	AnimationComponent* animationComponent;


public:

	Entity();
	virtual ~Entity();

	//Componet Function
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent( sf::Texture& texture_sheet);

	//Function

	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);



	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};
#endif
