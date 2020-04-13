#include "About.h"
#include "SFML/Graphics.hpp"
#include "string"
#include "sstream"
#include <iostream>
using namespace std;
About::About()
{
}

About::~About()
{
    //dtor
}
//Afficher les crédits (Développeurs du jeu)
int About::show(sf::RenderWindow& window)
{
 if (!font.loadFromFile("arial.ttf")) {
        // handle error
    }
    stringstream convert;

    convert = stringstream();
    convert << "   Jeu réalisé par Dupont Alexandre," << endl;
    convert << "   El Koukouchi Bilal,Laderriere Loic" << endl;
    convert << "étudiants de la HELHa Campus Mons " << endl;
    convert << "dans le cadre du cour de Mr.V.Altares" << endl<< endl;
    convert << "              (Press esc to return)" << endl;
    about.setFont(font);
    about.setFillColor(sf::Color::Blue);
    about.setString(convert.str());
    sf::FloatRect textRect = about.getLocalBounds();
    about.setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
    about.setPosition(window.getSize().x/2,window.getSize().y/2);

window.draw(about);
window.display();
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == (sf::Keyboard::Escape)) {//Si on appuye sur "esc" retour au menu
                    return 0;
                }
            }
        }
    }
}
