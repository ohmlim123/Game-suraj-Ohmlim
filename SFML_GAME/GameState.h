#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "State.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"PlayerGui.h"
#include"Bullet.h"




class PauseMenu;
class Player;
class PlayerGui;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;



class GameState :
	public State
{
private:

	float down_timer;
	float bullet_timer;

	float direction;

	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	
	sf::Font font;
	PauseMenu* pmenu;

	sf::Shader core_shader;

	Player* player;
	PlayerGui* playerGui;
	sf::Texture texture;

	std::vector<Bullet*> bullets;

	TileMap* tileMap;

	//Fanction
	void initDefferedRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShader();
	void initPlayers();
	void initPlayerGui();
	void initTileMap(std::string Map_name);
	
public :
	GameState(StateData* state_data,int stage_number);
	virtual ~GameState();
	
	
	
	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGui(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);


};

#endif 

