#include "Wizard.h"
#include <sstream>
#include <iostream>
using namespace std;
//Sort du hero
Spell Wizard::spellWizard1("Thunder","55 dmg with 2 range.",55,2,DAMAGE);
Spell Wizard::spellWizard2("HealBeam","45 dmg with 4 range.",45,4,DAMAGE);
Spell Wizard::spellWizard3("FireBurn","25 dmg with 6 range.",25,6,DAMAGE);
Spell Wizard::spellWizard4("IceBeam","10 dmg with 8 range.",10,8,DAMAGE);

Wizard::Wizard(string name,int hp,int movement):Hero(name,hp,movement){
    addSpell(&spellWizard1);
    addSpell(&spellWizard2);
    addSpell(&spellWizard3);
    addSpell(&spellWizard4);
}

Wizard::~Wizard(){

}

Wizard::Wizard(const Wizard& other):Hero(other){ //CONSTRUCTEUR DE COPIE

}

Wizard& Wizard::operator=(const Wizard& rhs){ //OPERATEUR D'AFFECTATION
    if(this == &rhs) return *this;
    Hero::operator=(rhs);

    return *this;
}

string Wizard::str()const{
    stringstream result;
    result<<Hero::str();
    return result.str();
}

Hero* Wizard::clone()const{
    return new Wizard(*this);
}
