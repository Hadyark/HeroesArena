#pragma once
#include "SFML/Graphics.hpp"
#include "Hero.h"
#define MAX_NUMBER_OF_ITEMS 4

class Hud
{
    public:
        Hud();
        virtual ~Hud();
        void DisplayInfoHero(Hero& hero, sf::Color color);
        void draw(sf::RenderWindow &window);

    protected:

    private:
    sf::Font font;
	sf::Text info[MAX_NUMBER_OF_ITEMS];
};

