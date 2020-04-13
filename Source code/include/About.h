#pragma once
#include "SFML/Graphics.hpp"

class About
{
    public:
        About();
        virtual ~About();
        int show(sf::RenderWindow &window);

    protected:

    private:
         sf::Font font;
         sf::Text about;
};
