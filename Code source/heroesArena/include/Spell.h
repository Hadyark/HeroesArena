#ifndef SPELL_H
#define SPELL_H
#include <string>
using namespace std;

enum Effect { DAMAGE, HEAL, DOT }; //LISTE DES EFFETS

class Spell
{
    private:
        string name; //NOM DU SORT
        string describe; //DESCRIPTION DU SORT LISIBLE PAR LE JOUEUR

        int power; //PUISSANCE DU SORT
        int range; //NOMBRE DE CASES DE PORTEE DU SORT
        Effect effect; //EFFET DU SORT

        int* id; //Check coherance
        static int compteur;

    public:
        //FORME CANONIQUE
        Spell(string name="Nom",string describe="Description", int power=0, int range=0, Effect effect=DAMAGE);//CONSTRUCTEUR
        virtual ~Spell(); //DESTRUCTEUR
        Spell(const Spell& other); //CONCTRUCTEUR DE COPIE
        Spell& operator=(const Spell& rhs); //OPERATEUR D'AFFECTATION

        //LES GETTERS
        string getName()const;
        string getDescribe()const;
        int getPower()const;
        int getRange()const;
        Effect getEffect()const;

        //GESTION CLONE POUR AJOUT DANS LES LISTES
        virtual Spell* clone()const;

        //AFFICHAGE console
        string str()const;
};

#endif // SPELL_H
