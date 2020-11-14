#include"stdafx.h"
#include "EditorState.h"
//Initializer Function

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0,0,static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 500.f;
	this->layer = 0;
	this->tileAddLock = false;

}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<int>(this->stateData->gfxSettings->resolution.width),
		static_cast<int>(this->stateData->gfxSettings->resolution.height)));

		this->view.setCenter(
			static_cast<int>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<int>(this->stateData->gfxSettings->resolution.height) / 2.f);
}

void EditorState::initBackground()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//BackGround
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)));

	this->backgroundTexture.loadFromFile("Resources/Images/background/cloud.png");


	this->background.setTexture(&this->backgroundTexture);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error ::Editor state to upload Fonts!!");
	}
}

void EditorState::initText()
{
	

	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y );
	
	
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
	this->pmenu->addButton("LOAD", gui::p2pY(55.5f,vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calCharSize(vm), "Load");
}


void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Blue);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f, 500.f, 500.f,
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font,"X"
	);


}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,
		"Resources/Images/Tile/tilemap5.png"
	);
}


EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initBackground();
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

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

		delete this->textureSelector;
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

	//Add a title to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				if (this->tileAddLock)
				{
					if (this->tileMap->TileEmpty(this->mousePosGrid.x, this->mousePosGrid.y, 0))
					{
						this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
				}
				
				
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	//Remove a title to the tilemap
	
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{

			if (!this->textureSelector->getActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}

	//Toggle Colision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else 
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
	{
		//Ghange to limit max type
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if(this->type > 0)
		--this->type;
	}

	//Set lock on / off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_TILE_LOCK"))) && this->getKeytime())
	{
		if (this->tileAddLock)
			this->tileAddLock = false;
		else
			this->tileAddLock = true;
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
	
	this->textureSelector->update(this->mousePosWindow,dt);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);

		this->selectorRect.setPosition(
			this->mousePosGrid.x * this->stateData->gridSize,
			this->mousePosGrid.y * this->stateData->gridSize
		);
	}
	


	this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type << 
		"\n" << "Tiles" << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer) << 
		"\n" << "Tile Lock: " << this->tileAddLock
		;
	this->cursorText.setString(ss.str());

	
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
	if (!this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}
	
	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);
	
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


	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
	
	
	
}
