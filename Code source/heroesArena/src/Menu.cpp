#include "Menu.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include <iostream>
Menu::Menu()
{

}

Menu::Menu(float width, float height)//Crée le menu
{
    if (!font.loadFromFile("arial.ttf")) {
        // handle error
    }
    sf::FloatRect menuRect;
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    menuRect = menu[0].getLocalBounds();
    menu[0].setOrigin(menuRect.left + menuRect.width/2.0f,0);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("About");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    menuRect = menu[1].getLocalBounds();
    menu[1].setOrigin(menuRect.left + menuRect.width/2.0f,0);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
    menuRect = menu[2].getLocalBounds();
    menu[2].setOrigin(menuRect.left + menuRect.width/2.0f,0);

    selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()//Se déplacer vers le haut dans le menu
{
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void Menu::moveDown()//Se déplacer vers le bas dans le menu
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

int Menu::show(sf::RenderWindow& window)//affiche le menu principal
{
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    menu.moveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.moveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.getPressedItem()) {
                    case 0:
                        std::cout << "Play button has been pressed" << std::endl;
                        //window.close();
                        //Game::Start();
                        return 1;
                        break;
                    case 1:
                        std::cout << "About button has been pressed" << std::endl;
                        return 2;
                        break;
                    case 2:
                        window.close();
                        break;
                    }

                    break;
                }

                break;
            case sf::Event::Closed:
                window.close();

                break;
            }
        }

        window.clear();
        sf::Texture textureImgMenu;
        if (!textureImgMenu.loadFromFile("assets/img/background_Menu.jpg"))
        {
            // erreur...
        }

        sf::Sprite spriteMenu;
        spriteMenu.setTexture(textureImgMenu);
        spriteMenu.setScale(1280 / spriteMenu.getLocalBounds().width, 720 / spriteMenu.getLocalBounds().height);
        window.draw(spriteMenu);
         sf::VertexArray rectangle(sf::Quads, 4);
        rectangle[0].position = sf::Vector2f(590, 0);
        rectangle[1].position = sf::Vector2f(690, 0);
        rectangle[2].position = sf::Vector2f(690, 720);
        rectangle[3].position = sf::Vector2f(590, 720);
        rectangle[0].color = sf::Color::Black;
        rectangle[1].color = sf::Color::Black;
        rectangle[2].color = sf::Color::Black;
        rectangle[3].color = sf::Color::Black;

        window.draw(rectangle);
        menu.draw(window);

        window.display();
    }
}

