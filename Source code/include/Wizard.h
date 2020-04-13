#ifndef WIZARD_H
#define WIZARD_H
#include "Hero.h"
#include "Spell.h"
#include <string>
#include <vector>

class Wizard : public Hero
{
    private:
        static Spell spellWizard1;
        static Spell spellWizard2;
        static Spell spellWizard3;
        static Spell spellWizard4;

    public:
        //FORME CANNONIQUE
        Wizard(string name="Wizard",int hp=200,int movement=3);//CONSTRUCTEUR
        virtual ~Wizard(); //DESTRUCTEUR
        Wizard(const Wizard& other); //CONCTRUCTEUR DE COPIE
        Wizard& operator=(const Wizard& rhs); //OPERATEUR D'AFFECTATION

        //AUTRES
        virtual Hero* clone()const; //CREER UN CLONE POUR AJOUTER DANS LES LISTES
        string str()const; //AFFICHAGE
};

#endif // WIZARD_H
