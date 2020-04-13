#include "Hud.h"
#include "SFML/Graphics.hpp"
#include "string"
#include "sstream"
Hud::Hud()
{
    //ctor
}

Hud::~Hud()
{
    //dtor
}

void Hud::DisplayInfoHero(Hero& hero, sf::Color color){//Affiche le hud dans battle
     if (!font.loadFromFile("arial.ttf")) {
        // handle error
    }
    //cout<<hero.str()<<endl;
    string result;
    stringstream convert;

    for(int i = 0; i<=3; i++){
        info[i].setFont(font);
        info[i].setCharacterSize(20);
        info[i].setFillColor(color);

    }
    convert = stringstream();
    if(hero.getAlreadyPlayed()){
        convert<<hero.getName()<<" (Already played)";
    }else{
        convert<<hero.getName()<<" (Not again played)";
    }
    info[0].setString(convert.str());
    info[0].setPosition(5.0f,5.0f);

    convert = stringstream();
    convert<< hero.getCHp()<<" / "<<hero.getHp();
    info[1].setString("Hp: " + convert.str());
    info[1].setPosition(5.0f,25.0f);

    convert = stringstream();
    convert<<"Movement: "<<hero.getCMovement()<<"/"<<hero.getMovement();
    info[2].setString(convert.str());
    info[2].setPosition(5.0f,45.0f);

    convert = stringstream();
    //convert<< "Spells : " << endl;
    int countSpell=0;
    for(Spell* s : hero.getSpells()) {
            countSpell++;
        convert <<"Key "<< countSpell << ") " << s->getName() << " : " << s->getDescribe() << endl;
    }
    info[3].setString(convert.str());
    info[3].setPosition(5.0f,65.0f);

}

void Hud::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(info[i]);
    }
}
