#include "Priest.h"
#include <sstream>
#include <iostream>
using namespace std;

Spell sP1("ShadowMind","35 dmg with 2 range",35,2,DAMAGE);
Spell sP2("ThunderLight","15 dmg with 4 range.",15,4,DAMAGE);
Spell sP3("SoftHeal","15 heal with 4 range.",-15,4,HEAL);
Spell sP4("HeavyHeal","35 heal with 2 range.",-35,2,HEAL);

Priest::Priest(string name,int hp,int movement):Hero(name,hp,movement){
    addSpell(&sP1);
    addSpell(&sP2);
    addSpell(&sP3);
    addSpell(&sP4);
}

Priest::~Priest(){

}

Priest::Priest(const Priest& other):Hero(other){ //CONSTRUCTEUR DE COPIE

}

Priest& Priest::operator=(const Priest& rhs){ //OPERATEUR D'AFFECTATION
    if(this == &rhs) return *this;
    Hero::operator=(rhs);

    return *this;
}

string Priest::str()const{
    stringstream result;
    result<<Hero::str();
    return result.str();
}

Hero* Priest::clone()const{
    return new Priest(*this);//new Priest(*this); <- Constructeur de copie
}
