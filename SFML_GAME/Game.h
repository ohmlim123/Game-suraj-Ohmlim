#ifndef GAME_H
#define GAME_H

#include"MainMenuState.h"

class Game
{
private:
	


	//Variable
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;


	
	std::map<std::string, int> supportedKeys;

	float gridSize;
	
	//Initialization

	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateDate();
	void iniStates();
	

public:

	Game();
	virtual ~Game();

	//Function

	void endApplication();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};
#endif