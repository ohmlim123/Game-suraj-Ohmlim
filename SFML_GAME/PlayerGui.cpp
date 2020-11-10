#include "stdafx.h"
#include "PlayerGui.h"

void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/Petchlamoon-Regular.ttf");
}

void PlayerGui::initLevelBar()
{
	float width = 30.f;
	float height = 30.f;
	float x = 20.f;
	float y = 10.f;

	

	this->levelBarText.setFont(this->font);


	this->levelbarback.setSize(sf::Vector2f(width, height));
	this->levelbarback.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelbarback.setPosition(x, y);

	

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(20);
	this->levelBarText.setPosition(this->levelbarback.getPosition().x + 10.f, this->levelbarback.getPosition().y + 5.f);
}



void PlayerGui::initEXPbar()
{
	float width = 700.f;
	float height = 60.f;
	float x = 20.f;
	float y = 60.f;

	this->expbarMaxWidth = width;

	this->expBarText.setFont(this->font);


	this->expbarback.setSize(sf::Vector2f(width, height));
	this->expbarback.setFillColor(sf::Color(50, 50, 50, 200));
	this->expbarback.setPosition(x, y);

	this->expbarinner.setSize(sf::Vector2f(width, height));
	this->expbarinner.setFillColor(sf::Color(20, 20, 250, 200));
	this->expbarinner.setPosition(this->expbarback.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(20);
	this->expBarText.setPosition(this->expbarinner.getPosition().x + 10.f, this->expbarinner.getPosition().y + 5.f);
}

void PlayerGui::initHPBar()
{
	float width = 700.f;
	float height = 60.f;
	float x = 20.f;
	float y = 140.f;

	this->hpbarMaxWidth = width;

	this->hpBarText.setFont(this->font);


	this->hpbarback.setSize(sf::Vector2f(width, height));
	this->hpbarback.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpbarback.setPosition(x, y);

	this->hpbarinner.setSize(sf::Vector2f(width, height));
	this->hpbarinner.setFillColor(sf::Color(250, 50, 50, 200));
	this->hpbarinner.setPosition(this->hpbarback.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(20);
	this->hpBarText.setPosition(this->hpbarinner.getPosition().x + 10.f, this->hpbarinner.getPosition().y + 5.f);

}
PlayerGui::PlayerGui(Player* player)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initEXPbar();
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
