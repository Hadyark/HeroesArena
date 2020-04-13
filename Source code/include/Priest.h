#ifndef PRIEST_H
#define PRIEST_H
#include "Hero.h"
#include "Spell.h"
#include <string>
#include <vector>

class Priest : public Hero
{
    private:

    public:
        //FORME CANNONIQUE
        Priest(string name="Priest",int hp=250,int movement=2);//CONSTRUCTEUR
        virtual ~Priest(); //DESTRUCTEUR
        Priest(const Priest& other); //CONCTRUCTEUR DE COPIE
        Priest& operator=(const Priest& rhs); //OPERATEUR D'AFFECTATION

        //AUTRES
        virtual Hero* clone()const; //CREER UN CLONE POUR AJOUTER DANS LES LISTES
        string str()const; //AFFICHAGE
};

#endif // PRIEST_H
