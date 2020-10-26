#include"MainMenuState.h"

void MainMenuState::iniFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		std::cout << "Could not load font!!";
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs;

	ifs.open("Config/gamestate_keybinds.ini");

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

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	:State(window, supportedKeys)
{
	this->iniFonts();
	this->initKeybinds();


	this->gamestate_btn = new Button(100,100,150,150,
		&this->font,"NEW Game",
		sf::Color(70,70,70,200) , 
		sf::Color(150, 150, 150, 200) , 
		sf::Color(20, 20, 20 , 200));


	this->background.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);

}
MainMenuState::~MainMenuState()
{
	delete this->gamestate_btn;
}

void MainMenuState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForquit();



	
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);


	this->gamestate_btn->update(this->mousePosView);
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	
	target->draw(this->background);

	this->gamestate_btn->render(target);

}
