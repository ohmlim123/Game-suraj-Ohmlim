#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(float x, float y,float z)
{
	this->texture_bullet.loadFromFile("Resources/Images/Sprite/bullet/sword_wave2.png");
	this->sword_wave.setPosition(x, y);
	this->sword_wave.setTexture(texture_bullet);
	direction = z;	
	this->sword_wave.setScale(-1* direction, 2);
	 

	speed = 10.f;
	
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
	this->sword_wave.move(direction * speed, 0.f);
}

void Bullet::render(sf::RenderTarget& target)
{


	target.draw(sword_wave);
}
