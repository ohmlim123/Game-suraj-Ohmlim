#ifndef MAINMANUSTATE_H
#define MAINMENUSTATE_H

#include"GameState.h"
#include"Button.h"

class MainMenuState :
	public State
{


private:

	//Variable
	sf::RectangleShape background;

	

	//Fanction
	void iniFonts();
	void initKeybinds();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();


	void endState();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);

};
#endif