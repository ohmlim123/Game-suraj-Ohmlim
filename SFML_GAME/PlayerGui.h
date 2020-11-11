#pragma once

#include"Player.h"

class Player;
class sf::RectangleShape;

class PlayerGui
{
private:
	

	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	//Level bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelbarback;
	

	//EXP bar
	std::string expBarString;
	sf::Text expBarText;
	float expbarMaxWidth;
	sf::RectangleShape expbarback;
	sf::RectangleShape expbarinner;


	//HP bar 
	std::string hpBarString;
	sf::Text hpBarText;
	float hpbarMaxWidth;
	sf::RectangleShape hpbarback;
	sf::RectangleShape hpbarinner;


	void initFont();
	//void initLevelBar();
	//void initEXPbar();
	void initHPBar();

public:
	PlayerGui(Player* player,sf::VideoMode& vm);
	virtual ~PlayerGui();


	//functions
	void updateLevelbar();
	void updateEXPbar();
	void updateHPbar();
	void update(const float& dt);


	void renderLevelbar(sf::RenderTarget& target);
	void renderEXPbar(sf::RenderTarget& target);
	void renderHPbar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

