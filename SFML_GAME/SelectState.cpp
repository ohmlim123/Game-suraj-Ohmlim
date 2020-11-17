#include "stdafx.h"
#include "SelectState.h"

void SelectState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SelectState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error to upload Fonts!!");
	}
}

void SelectState::initKeybinds()
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

void SelectState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;


	//BackGround
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/background3.png");


	this->background.setTexture(&this->backgroundTexture);
	//Buttons
	this->buttons["LEVEL1"] = new gui::Button(
		gui::p2pX(20.5f, vm), gui::p2pY(15.9f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Level1", gui::calCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["LEVEL2"] = new gui::Button(
		gui::p2pX(20.5f, vm), gui::p2pY(35.9f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Level2", gui::calCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["LEVEL3"] = new gui::Button(
		gui::p2pX(20.5f, vm), gui::p2pY(55.9f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Level3", gui::calCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(70.5f, vm), gui::p2pY(75.9f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));



	//Mode
	std::vector<std::string>modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	

	
	
}

void SelectState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	this->initGui();
}

SelectState::SelectState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();

	
}

SelectState::~SelectState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions
void SelectState::updateInput(const float& dt)
{

}
void SelectState::updateGui(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["LEVEL1"]->isPressed())
	{
		this->states->push(new GameState(this->stateData,1));
	}

	if (this->buttons["LEVEL2"]->isPressed())
	{
		this->states->push(new GameState(this->stateData, 2));
	}

	if (this->buttons["LEVEL3"]->isPressed())
	{
		this->states->push(new GameState(this->stateData, 3));
	}

	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
}
void SelectState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateGui(dt);

}
void SelectState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
void SelectState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->background);


	this->renderGui(*target);
}
