#include"Game.h"

void Game::initWindow()
{
    
    std::ifstream ifs("Config/window.ini");
    
    std::string title = "None";
    sf::VideoMode window_bounds(800,600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;


    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }


    ifs.close();

	this->window = new sf::RenderWindow(window_bounds,title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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

        this->states.push(new MainMenuState(this->window, &this->supportedKeys));
        this->states.push(new GameState(this->window, &this->supportedKeys));
 
    
}

Game::Game()
{
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
