#ifndef GUI_H
#define GUI_H




enum button_states{BTN_IDLE = 0,BTN_HOVER,BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:

		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color  outlineIdleColor;
		sf::Color  outlineHoverColor;
		sf::Color  outlineActiveColor;



	public:
		Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
			sf::Color outline_idle_Color = sf::Color::Transparent, sf::Color outline_hover_Color = sf::Color::Transparent, sf::Color outline_active_Color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();
		
		//Accessors

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifier

		void setText(const std::string text);
		void setId(const short unsigned id);

		//Function
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime;
		const float keytimeMax;


		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
		
		
	public:

		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;

		//Funcituon
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow,const float& dt);
		void render(sf::RenderTarget& target);
	};


	class TextureSelector
	{
	private:
		float keytime;
		float keytimeMax;
		float gridSize;
		bool active;
		bool hiden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		


	public:
		TextureSelector(float x,float y,float width, float height,  float gridSize,const sf::Texture* texture_sheet,sf::Font& font,std::string text);
		~TextureSelector();

		//Accessor
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow,const float& dt);
		void render(sf::RenderTarget& target);

	};

}
#endif

