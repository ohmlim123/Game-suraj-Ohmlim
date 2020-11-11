#include "stdafx.h"
#include "PlayerGui.h"
#include"Gui.h"

void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf");
}

/*void PlayerGui::initLevelBar()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	

	this->levelBarText.setFont(this->font);


	this->levelbarback.setSize(sf::Vector2f(width, height));
	this->levelbarback.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelbarback.setPosition(x, y);

	

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calCharSize(this->vm,80));
	this->levelBarText.setPosition(
		this->levelbarback.getPosition().x + gui::p2pX(0.53f,this->vm),
		this->levelbarback.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}



void PlayerGui::initEXPbar()
{
	float width = gui::p2pX(36.4f,this->vm);
	float height = gui::p2pY(5.5f,this->vm);
	float x = gui::p2pX(1.f,this->vm);
	float y = gui::p2pY(6.5f,this->vm);

	this->expbarMaxWidth = width;

	this->expBarText.setFont(this->font);


	this->expbarback.setSize(sf::Vector2f(width, height));
	this->expbarback.setFillColor(sf::Color(50, 50, 50, 200));
	this->expbarback.setPosition(x, y);

	this->expbarinner.setSize(sf::Vector2f(width, height));
	this->expbarinner.setFillColor(sf::Color(20, 20, 250, 200));
	this->expbarinner.setPosition(this->expbarback.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(gui::calCharSize(this->vm,80));
	this->expBarText.setPosition(
		this->expbarinner.getPosition().x + gui::p2pX(0.53f, this->vm), 
		this->expbarinner.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}
*/
void PlayerGui::initHPBar()
{
	float width = gui::p2pX(36.4f,this->vm);
	float height = gui::p2pY(5.5f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->hpbarMaxWidth = width;

	this->hpBarText.setFont(this->font);


	this->hpbarback.setSize(sf::Vector2f(width, height));
	this->hpbarback.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpbarback.setPosition(x, y);

	this->hpbarinner.setSize(sf::Vector2f(width, height));
	this->hpbarinner.setFillColor(sf::Color(250, 50, 50, 200));
	this->hpbarinner.setPosition(this->hpbarback.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::calCharSize(this->vm,120));
	this->hpBarText.setPosition(
		this->hpbarinner.getPosition().x + gui::p2pX(0.53f,this->vm), 
		this->hpbarinner.getPosition().y + gui::p2pY(0.5f,this->vm)
	);

}
PlayerGui::PlayerGui(Player* player, sf::VideoMode& vm)
	:vm(vm)
{
	this->player = player;

	this->initFont();
	//this->initLevelBar();
	//this->initEXPbar();
	this->initHPBar();

}

PlayerGui::~PlayerGui()
{

}

//functions

void PlayerGui::updateLevelbar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);

}

void PlayerGui::updateEXPbar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);




	this->expbarinner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expbarMaxWidth * percent)),
			this->expbarinner.getSize().y
		)
	);


	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGui::updateHPbar()
{

	float percent = static_cast<float>( this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);




	this->hpbarinner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpbarMaxWidth * percent)),
			this->hpbarinner.getSize().y
		)
	);


	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGui::update(const float& dt)
{
	this->updateLevelbar();
	this->updateEXPbar();
	this->updateHPbar();
}

void PlayerGui::renderLevelbar(sf::RenderTarget& target)
{
	target.draw(this->levelbarback);
	
	target.draw(this->levelBarText);
}

void PlayerGui::renderEXPbar(sf::RenderTarget& target)
{
	target.draw(this->expbarback);
	target.draw(this->expbarinner);
	target.draw(this->expBarText);
}

void PlayerGui::renderHPbar(sf::RenderTarget& target)
{
	target.draw(this->hpbarback);
	target.draw(this->hpbarinner);
	target.draw(this->hpBarText);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderLevelbar(target);
	this->renderEXPbar(target);
	this->renderHPbar(target);
}
