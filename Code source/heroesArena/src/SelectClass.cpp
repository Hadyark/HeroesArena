#include "SelectClass.h"
#include "Wizard.h"
#include "Warrior.h"
#include "Priest.h"
#include "SFML/Graphics.hpp"

SelectClass::SelectClass(float resolutionX, float resolutionY)//Affiche le menu de selection des classes
{
    if (!font.loadFromFile("arial.ttf")) {
        // handle error
    }

    txtSelect.setFont(font);
    txtSelect.setFillColor(sf::Color::White);
    txtSelect.setString("    Select your classes \n (Right/Left switch class)");
    txtSelect.setPosition(sf::Vector2f(resolutionX / 2, resolutionY/ (MAX_NUMBER_OF_ITEMS + 1) * 0));
    sf::FloatRect textRect = txtSelect.getLocalBounds();
    txtSelect.setOrigin(textRect.left + textRect.width/2.0f,0);

    vector<Hero*> heross(4);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS; i++){
        heross[i] = new Wizard;
        menu[i].setFont(font);
        menu[i].setString("<"+heross[selectedItemIndex]->getName()+">");
        sf::FloatRect textRect = menu[i].getLocalBounds();
        menu[i].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);

    }
    heros=heross;
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setPosition(sf::Vector2f(resolutionX / 2, resolutionY/ (MAX_NUMBER_OF_ITEMS + 1) * 1));
    menu[0].setCharacterSize(40);

    menu[1].setFillColor(sf::Color::Blue);
    menu[1].setPosition(sf::Vector2f(resolutionX / 2, resolutionY/ (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFillColor(sf::Color::Red);
    menu[2].setPosition(sf::Vector2f(resolutionX / 2, resolutionY/ (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFillColor(sf::Color::Red);
    menu[3].setPosition(sf::Vector2f(resolutionX / 2, resolutionY/ (MAX_NUMBER_OF_ITEMS + 1) * 4));

    selectedItemIndex = 0;
}

SelectClass::~SelectClass()
{
    //dtor
}
vector<Hero*> SelectClass::show(sf::RenderWindow& window)
{

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            moveUp();
                            break;
                        case sf::Keyboard::Down:
                            moveDown();
                            break;
                        case sf::Keyboard::Right:
                            selectRight();
                            break;
                        case sf::Keyboard::Left:
                            selectLeft();
                            break;
                        case sf::Keyboard::Enter:
                            return heros; // Retourne la liste des héros selectionés
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear();

        for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
        }
        window.draw(txtSelect);
        window.display();
    }
}
void SelectClass::moveUp()//Se déplacer vers le haut dans le menu
{
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setCharacterSize(30);
        selectedItemIndex--;
        menu[selectedItemIndex].setCharacterSize(40);
    }
}
void SelectClass::moveDown()//Se déplacer vers le bas dans le menu
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setCharacterSize(30);
        selectedItemIndex++;
        menu[selectedItemIndex].setCharacterSize(40);
    }
}
void SelectClass::selectLeft()//Change de classe
{
    if(heros[selectedItemIndex]->getName()=="Warrior"){
        heros[selectedItemIndex]= new Priest;
    }
    else if(heros[selectedItemIndex]->getName()=="Wizard"){
        heros[selectedItemIndex]= new Warrior;
    }
    else if(heros[selectedItemIndex]->getName()=="Priest"){
        heros[selectedItemIndex]= new Wizard;
    }
    menu[selectedItemIndex].setString("<"+heros[selectedItemIndex]->getName()+">");

}
void SelectClass::selectRight()//Change de classe
{
    if(heros[selectedItemIndex]->getName()=="Warrior"){
        heros[selectedItemIndex]= new Wizard;
    }
    else if(heros[selectedItemIndex]->getName()=="Wizard"){
        heros[selectedItemIndex]= new Priest;
    }
    else if(heros[selectedItemIndex]->getName()=="Priest"){
        heros[selectedItemIndex]= new Warrior;
    }
    menu[selectedItemIndex].setString("<"+heros[selectedItemIndex]->getName()+">");
}
