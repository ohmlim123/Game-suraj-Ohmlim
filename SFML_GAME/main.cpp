#include"stdafx.h"
#include "Entity.h"
#include"Game.h"
#include"Bullet.h"
#include"Player.h"
#include"AnimationComponent.h"
#include"MovementComponent.h"


int main()
{
    Game game;


    game.run();

    /*float bull = 0.f;
    sf::Clock bulltime;
    std::vector<Bullet> bullet;
    sf::Texture bullet_texture;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(), 0, sf::Vector2f(this->sprite.GetPosition().x + 10, this->sprite.GetPosition().y)));
    }

    for (Bullet& bullet : bullet)
        bullet.updateBullet(dt);



    for (Bullet& bullet : bullet)
        bullet.Draw(this->window);*/
   
    return 0;
}