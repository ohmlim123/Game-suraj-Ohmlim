#include"MainMenuState.h"


//Initializer Function
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
		static_cast<float>(this->window->getSize().x), 
		static_cast<float>(this->window->getSize().y)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/bg2.png");
	

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Rodwick.otf"))
	{
		throw("Error to upload Fonts!!");
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(850, 200, 250, 50,
		&this->font, "NEW Game",
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	this->buttons["SETTINGS"] = new Button(850, 350, 250, 50,
		&this->font, "Settings",
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	this->buttons["EXIT_STATE"] = new Button(850,600, 250, 50,
		&this->font, "Quit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys,states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	


	

}
MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState!" << "\n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForquit();



	
}

void MainMenuState::updateButtons()
{
	// Update all the button in the state 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	
	//New Gmae
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this-> window, this->supportedKeys,this->states));
	}

	//Quit this Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);


	
	this->updateButtons();

	
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	
	target->draw(this->background);

	
	this->renderButtons(target);


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
