#include "SettingState.h"

void SettingState::initVariables()
{

}

void SettingState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/bg2.png");


	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error to upload Fonts!!");
	}
}

void SettingState::initKeybinds()
{
	std::ifstream ifs;

	ifs.open("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{

		std::string key = "";
		std::string key2 = "";


		while (ifs >> key >> key2)
		{

			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}



	ifs.close();
}

void SettingState::initButtons()
{

	this->buttons["EXIT_STATE"] = new gui::Button(1550.f, 820.f, 250.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys,states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


//Accessor


//funstion

void SettingState::updateInput(const float& dt)
{





}

void SettingState::updateButtons()
{
	// Update all the button in the state 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	
	//Setting


	

	//Quit this Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void SettingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);



	this->updateButtons();


}

void SettingState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->background);


	this->renderButtons(*target);


	//REMOVE LATER
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
