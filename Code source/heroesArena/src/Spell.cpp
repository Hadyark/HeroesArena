#include "Spell.h"
#include <sstream>
#include <iostream>
using namespace std;

int Spell::compteur = 0;

//FORME CANONIQUE
Spell::Spell(string name,string describe, int power, int range, Effect effect){ //CONSTRUCTEUR
    this->name = name;
    this->describe = describe;
    this->power = power;
    this->range = range;
    this->effect = effect;

    compteur++;
    id=new int; //important
    *id=compteur; //important
}

Spell::~Spell(){ //DESTRUCTEUR
    delete id;
}

Spell::Spell(const Spell& other){ //CONCTRUCTEUR DE COPIE
    this->name = other.name;
    this->describe = other.describe;
    this->power = other.power;
    this->range = other.range;
    this->effect = other.effect;
    id = new int(*other.id);
}

Spell& Spell::operator=(const Spell& rhs){ //OPERATEUR D'AFFECTATION
    if(this == &rhs) return *this;

    this->name = rhs.name;
    this->describe = rhs.describe;
    this->power = rhs.power;
    this->range = rhs.range;
    this->effect = rhs.effect;

    delete id;
    id=new int (*rhs.id);

    return *this;
}

//LES GETTERS
string Spell::getName()const{
    return name;
}

string Spell::getDescribe()const{
    return describe;
}

int Spell::getPower()const{
    return power;
}

int Spell::getRange()const{
    return range;
}

Effect Spell::getEffect()const{
    return effect;
}

Spell* Spell::clone()const{
    return new Spell(*this);
}

//AFFICHAGE console
string Spell::str()const{ //AFFICHAGE
    stringstream result;
    result  <<"ID: "<<*id<<endl
            <<"Name: "<<name<<endl
            <<"Describe: "<<describe<<endl
            <<"Power: "<<power<<endl
            <<"Range: "<<range<<endl
            <<"Effect: "<<effect<<endl;
    return result.str();
}
