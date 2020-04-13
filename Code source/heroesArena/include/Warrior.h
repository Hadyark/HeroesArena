#ifndef WARRIOR_H
#define WARRIOR_H
#include "Hero.h"
#include "Spell.h"
#include <string>
#include <vector>

class Warrior : public Hero
{
    private:

    public:
        //FORME CANNONIQUE
        Warrior(string name="Warrior",int hp=500,int movement=4);//CONSTRUCTEUR
        virtual ~Warrior(); //DESTRUCTEUR
        Warrior(const Warrior& other); //CONCTRUCTEUR DE COPIE
        Warrior& operator=(const Warrior& rhs); //OPERATEUR D'AFFECTATION

        //AUTRES
        virtual Hero* clone()const; //CREER UN CLONE POUR AJOUTER DANS LES LISTES
        string str()const; //AFFICHAGE
};

#endif // WARRIOR_H
