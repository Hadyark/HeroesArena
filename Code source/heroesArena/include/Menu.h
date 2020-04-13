#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu();
	Menu(float width, float height);
	~Menu();
    int show(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem() { return selectedItemIndex; }
	//static void Start();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

