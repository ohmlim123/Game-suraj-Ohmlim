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
    SettingState(StateData* state_data);
    virtual ~SettingState();

    //Accessor



	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};
#endif

