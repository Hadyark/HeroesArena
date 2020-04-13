#include "Warrior.h"
#include <sstream>
#include <iostream>
using namespace std;

Spell sW1("Punch","80 dmg with 1 range.",80,1,DAMAGE);
Spell sW2("Kick","45 dmg with 3 range.",45,3,DAMAGE);
Spell sW3("Throw stone","15 dmg with 5 range.",15,5,DAMAGE);
Spell sW4("SelfHeal","25 heal with 0 range.",-25,0,HEAL);

Warrior::Warrior(string name,int hp,int movement):Hero(name,hp,movement){
    addSpell(&sW1);
    addSpell(&sW2);
    addSpell(&sW3);
    addSpell(&sW4);
}

Warrior::~Warrior(){

}

Warrior::Warrior(const Warrior& other):Hero(other){ //CONSTRUCTEUR DE COPIE

}

Warrior& Warrior::operator=(const Warrior& rhs){ //OPERATEUR D'AFFECTATION
    if(this == &rhs) return *this;
    Hero::operator=(rhs);

    return *this;
}

string Warrior::str()const{
    stringstream result;
    result<<Hero::str();
    return result.str();
}

Hero* Warrior::clone()const{
    return new Warrior(*this);
}
