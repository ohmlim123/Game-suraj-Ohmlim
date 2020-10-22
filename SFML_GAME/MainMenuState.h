/*#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
class MainMenuState :
    public State
{
private:
    
    sf::RectangleShape background;

    //Functions
    void initKeybinds();

public:
   MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~MainMenuState();


    void endState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
public:
    MainMenuState();
    virtual ~MainMenuState();
};
#endif*/

