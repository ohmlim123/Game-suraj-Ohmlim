#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variable
    bool attacking;

    //Initializer Function
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Function
    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);

};
#endif
