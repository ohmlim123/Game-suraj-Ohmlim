#include"stdafx.h"
#include "EditorState.h"
//Initializer Function

void EditorState::initVariables()
{
	
	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<int>(this->stateData->gfxSettings->resolution.width),
		static_cast<int>(this->stateData->gfxSettings->resolution.height)));

		this->view.setCenter(
			static_cast<int>(this->stateData->gfxSettings->resolution.width)  / 2,
			static_cast<int>(this->stateData->gfxSettings->resolution.height) / 2);
}

void EditorState::initBackground()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//BackGround
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/forest1.png");


	this->background.setTexture(&this->backgroundTexture);
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
void EditorState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),gui::calCharSize(vm), "Quit");
	this->pmenu->addButton("SAVE", gui::p2pY(64.8f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calCharSize(vm), "Save");
	this->pmenu->addButton("LOAD", gui::p2pY(35.5f,vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calCharSize(vm), "Load");
}


void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	


}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,
		"Resources/Images/Tile/Map_natural.png"
	);
}

void EditorState::initMode()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}


EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initBackground();
	this->initEditorStateData();
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

	this->initMode();

}
EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
		delete this->pmenu;
		 
		delete this->tileMap;

		

		for (size_t i = 0; i < this->modes.size(); i++)
		{
			delete this->modes[i];
		}
}


void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//MOVE VIEW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < this->modes.size() - 1)
		{
			this->activeMode++;
		}
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
			 if (this->activeMode > 0)
			{
				this->activeMode--;
			}
			 


	}
	
}

void EditorState::updateButtons()
{
	// Update all the button in the state 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	
}

void EditorState::updateGui(const float& dt)
{
	
	
	
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("text.slmp");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("text.slmp");
}

void EditorState::updateModes(const float& dt)
{
	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
	
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
		
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

	


}

void EditorState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
	

	if (!target)
		target = this->window;

	target->draw(this->background);

	
	target->setView(this->view);
	this->tileMap->render(*target,this->mousePosGrid);
	this->tileMap->renderDefferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	

	this->renderGui(*target);

	this->renderModes(*target);


	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
	
	
	
}
