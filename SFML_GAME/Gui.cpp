#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color)
{

	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_Color);
	

	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);

	this->text.setPosition(
		this->shape.getPosition(). x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition(). y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->activeColor = active_Color;

	

}
gui::Button::~Button()
{

}

//Accessors


const bool gui::Button::isPressed() const
{

	if (this->buttonState == BTN_ACTIVE)
		return true;


	return false;
}

const std::string& gui::Button::getText() const
{
	return this->text.getString();
}

//Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*update the booleans for hover and pressed*/
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// pressed

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);

}
 // DropDownList ===========================

gui::DropDownList::DropDownList(sf::Font& font ,std::string list[],unsigned nrOfElements ,unsigned default_index)
	: font(font)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);


	for (size_t i = 0; i < nrOfElements;i++)
	{

		this->list.push_back(new gui::Button(
			300.f, 200.f, 250.f, 50.f,
			&this->font, list[i], 50,
			sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		)
		);
	}
	this->activeEleement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList()
{
	delete this->activeEleement;
	for (auto *&i : this->list)
		delete  i;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos)
{

}

void gui::DropDownList::render(sf::RenderTarget& target)
{

}
