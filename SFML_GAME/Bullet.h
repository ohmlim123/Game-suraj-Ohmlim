#ifndef BULLET_H
#define BULLET_H


#include"HitboxComponent.h"

class HitboxComponent;

class Bullet
{
private:
	
	sf::Texture texture_bullet;
	sf::Sprite sword_wave;

	float direction;
	float speed;
	 
protected:

	HitboxComponent* hitboxComponent;

public:
	Bullet(float x,float y,float z);
	virtual ~Bullet();

	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);


	void update();
	void render(sf::RenderTarget& target);
};
#endif

