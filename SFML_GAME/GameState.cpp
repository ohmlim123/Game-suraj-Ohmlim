#include"stdafx.h"
#include"GameState.h"




//Initializer functions

void GameState::initDefferedRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0, 
		0, 
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<int>(this->stateData->gfxSettings->resolution.width),
				static_cast<int>(this->stateData->gfxSettings->resolution.height)

		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<int>(this->stateData->gfxSettings->resolution.width) / 2.f,
				static_cast<int>(this->stateData->gfxSettings->resolution.height) / 2.f

		)
	);
}


void GameState::initKeybinds()
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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf"))
	{
		throw("Error to upload Fonts!!");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprite/Player/wizard3.png"))
	{
		throw("Error Game State could not load player idle textures");
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT",gui::p2pY(74.f,vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calCharSize(vm), "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player,this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,"Resources/Images/Tile/tileofmap2.png");
	this->tileMap->loadFromFile("text.slmp");
}

//Contructor / Destructors
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDefferedRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();
	this->initPlayerGui();
	this->initTileMap();
}
GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGui;
	delete this->tileMap;
}


//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor (this->player->getPosition().y));
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))&& this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{

	//Update player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move( -1.f, 0.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move( 1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
		
		
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
		
		
	}
		

	
	

}

void GameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player,dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) // unpaused update
	{
		
		this->updateView(dt);

		this->updatePlayerInput(dt); 

		this->updateTileMap(dt);

		this->player->update(dt);
		
		this->playerGui->update(dt);

		
	}
	else // Puased update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	this->renderTexture.clear();

		this->renderTexture.setView(this->view);
		this->tileMap->render(this->renderTexture,this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

		this->player->render(this->renderTexture);
	
		this->tileMap->renderDefferred(this->renderTexture);

		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->playerGui->render(this->renderTexture);

		//Render GUI
		if (this->paused) // Puase maenu render
		{
			//this->renderTexture.setView(this->renderTexture.getDefaultView());
			this->pmenu->render(this->renderTexture);
		}
	
		//Final Render

		this->renderTexture.display();
		//this->renderSprite.setTexture(this->renderTexture.getTexture());
		target->draw(this->renderSprite);

}
