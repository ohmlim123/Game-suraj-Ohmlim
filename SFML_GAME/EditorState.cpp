#include "EditorState.h"
//Initializer Function

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{
	
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error ::Editor state to upload Fonts!!");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs;

	ifs.open("Config/editiorstate_keybinds.ini");

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

void EditorState::initButtons()
{
	
}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();






}
EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	// Update all the button in the state 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);



	this->updateButtons();


}

void EditorState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	


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
