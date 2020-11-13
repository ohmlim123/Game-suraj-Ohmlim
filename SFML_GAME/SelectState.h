#ifndef SELECTSTATE_H
#define SELECTSTATE_H

#include "State.h"
#include"Gui.h"
#include"GameState.h"
class SelectState :
	public State
{
private:
	//Variable

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;


	std::map<std::string, gui::Button*>buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;


	//Fanction
	void initVariables();

	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:

	SelectState(StateData* state_data);
	virtual ~SelectState();

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
	
};
#endif

