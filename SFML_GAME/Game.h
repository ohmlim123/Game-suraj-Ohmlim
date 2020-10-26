#ifndef GAME_H
#define GAME_H



#include"MainMenuState.h"






class Game
{
private:

	//Variable
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;


	
	std::map<std::string, int> supportedKeys;
	
	//Initialization

	void initWindow();
	void initKeys();
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