#ifndef SELECTCLASS_H
#define SELECTCLASS_H
#include "SFML/Graphics.hpp"
#include "Hero.h"

#define MAX_NUMBER_OF_ITEMS 4
using namespace std;
class SelectClass
{
    public:
        SelectClass(float width, float height);
        virtual ~SelectClass();
        vector<Hero*> show(sf::RenderWindow &window);
        void moveUp();
        void moveDown();
        void selectLeft();
        void selectRight();
    protected:

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Text txtSelect;
        vector<Hero*> heros;
};

#endif // SELECTCLASS_H
