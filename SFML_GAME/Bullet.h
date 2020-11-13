#pragma once
class Bullet
{
private:
	
	sf::Texture texture_bullet;
	sf::Sprite sword_wave;

	float direction;
	float speed;
	 

public:
	Bullet(float x,float y,float z);
	virtual ~Bullet();


	void update();
	void render(sf::RenderTarget& target);
};

