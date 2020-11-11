#include"stdafx.h"
#include "SettingState.h"

void SettingState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
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

void SettingState::initGui()
{

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;


	//BackGround
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/background1.png");


	this->background.setTexture(&this->backgroundTexture);
	//Buttons
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(70.5f,vm), gui::p2pY(75.9f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(60.7f, vm), gui::p2pY(75.9f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Apply", gui::calCharSize(vm),
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	//Mode
	std::vector<std::string>modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	//DropdwonList
	this->dropDownLists["RESOLUTION"] =  new gui::DropDownList(
		gui::p2pX(41.6f, vm), gui::p2pY(37.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(6.f, vm),
		font,modes_str.data(), modes_str.size()
	);

	//InitText
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f,vm), gui::p2pY(28.7,vm)));
	this->optionsText.setCharacterSize(gui::calCharSize(vm,70));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);
}

void SettingState::resetGui()
{

	/*
		Clears the Gui Element and re-intialishes the Gui

		@return void

	*/
	
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}



	this->dropDownLists.clear();

	this->initGui();
}



SettingState::SettingState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	
}


//Accessor


//funstion

void SettingState::updateInput(const float& dt)
{





}

void SettingState::updateGui(const float& dt)
{
	// Update all the button in the state 
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Button Funcctionality
	//Quit this Game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	//Apply selected setting
	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title,sf::Style::Default);

		this->resetGui();
	}

	//dropdownlists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	//dropdwn;ist functionality
	
}

void SettingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);



	this->updateGui(dt);

	
}

void SettingState::renderGui(sf::RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}

}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->background);


	this->renderGui(*target);

	target->draw(this->optionsText);
	


	//REMOVE LATER
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
