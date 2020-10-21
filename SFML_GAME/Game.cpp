#include "Game.h"
void Game::initWindow()
{
    /*Creates a SFML window using options from a window.ini file.*/
	this->window = new sf::RenderWindow(sf::VideoMode(400, 500), "OHMLIM'S GAME");
}
Game::Game()
{
    this->initWindow(); 
}

Game::~Game()
{

	delete this->window;
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
}

void Game::render()
{
    this->window->clear();
    
    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render(); 
    }
}

