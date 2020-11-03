#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H


#include "State.h"
#include"Gui.h"

class SettingState :
    public State
{
private:
	//Variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;


	std::map<std::string, gui::Button*>buttons;


	//Fanction
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
    SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingState();

    //Accessor



	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};
#endif

