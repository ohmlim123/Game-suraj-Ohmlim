#include"stdafx.h"
#include"Game.h"
//Static function 

//Initializer function
void Game::initVariables()
{
    this->window = NULL;
    
    this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}


void Game::initWindow()
{
    
   //Creat fsml window
    if (this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Fullscreen,
            this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings);
        

        


    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
    std::ifstream ifs;

    ifs.open("Config/supported_keys.ini");

    if (ifs.is_open())
    {
       
        std::string key = "";
        int key_value = 0;


        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
        
    }
    


    ifs.close();


    


    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }


}

void Game::iniStates()
{

        this->states.push(new MainMenuState(this->window, this->gfxSettings,&this->supportedKeys, &this->states));
        //this->states.push(new GameState(this->window, &this->supportedKeys));
 
    
}

//Contructors/Dustructors

Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->iniStates();
}

Game::~Game()
{
	delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
        
}

//Function

void Game::endApplication()
{
    std::cout << "eEnding Appilecation" << "\n";
}

void Game::updateDt()
{

    this->dt = dtClock.restart().asSeconds();

   
}

void Game::updateSFMLEvents()
{
    
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }

  
}

void Game::update()
{
    this->updateSFMLEvents();
   
    if (!this->states.empty())
    {

        this->states.top()->update(this->dt);
        
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();
    
    if (!this->states.empty())
        this->states.top()->render();
    
    this->window->display();

}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}


