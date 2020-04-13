#ifndef HERO_H
#define HERO_H
#include <string>
#include <vector>
#include "Spell.h"
#include "DisplayedObject.h"

using namespace std;

class Hero : public DisplayedObject
{
    private:
        string name; //LE NOM DU HERO

        int hp; //NOMBRE DE POINTS DE VIE MAXIMUM DU HERO
        int cHp; //NOMBRE DE POINTS DE VIE DU HERO EN JEU

        int movement; //NOMBRE DE CASES MAXIMUM DE DEPLACEMENT PAR TOUR DU HERO
        int cMovement; //NOMBRE DE CASES RESTANTES DE DEPLACEMENT PAR TOUR DU HERO
        bool alreadyPlayed;//SI LE HERO A DEJA JOUE
        int* id; //L'IDENTIFIANT UNIQUE DU HERO
        static int compteur; //LE COMPTEUR PERMETTANT DE CREER DES IDENTIFIANTS UNIQUES

        vector <Spell*> spells;//LA LISTE DES SORTS DU HERO

    public:
        //FORME CANONIQUE
        Hero(string name="nom",int hp=0,int movement=0);//CONSTRUCTEUR
        virtual ~Hero();//DESTRUCTEUR
        Hero(const Hero& other); //CONCTRUCTEUR DE COPIE
        Hero& operator=(const Hero& rhs); //OPERATEUR D'AFFECTATION

        //CRUD DES SPELLS
        void addSpell(Spell* s);//AJOUTER UN SORT A LA LISTE

        //AUTRES
        virtual string str()const; //AFFICHAGE CONSOLE DU HERO
        virtual Hero* clone()const; //CREER UN CLONE POUR AJOUTER DANS LES LISTES
        bool operator==(const Hero&)const; //COMPARER 2 HEROS
        bool isRanged(int rangeX, int rangeY, int range); //VERIFICATION DE LA DISTANCE ENTRE 2 HEROS
        bool movePossible(int moveX, int moveY); //VERIFICATION DE LA POSSIBILITE DE DEPLACEMENT DU HERO
        bool castSpell(Hero* h, Spell* s); //LANCER UN SORT

        //LES GETTERS
        string getName()const; //OBTENIR LE NOM DU HERO

        int getHp()const; //OBTENIR LES POINTS DE VIE DE BASE DU HERO
        void setHp(int newHp); //MODIFIER LES POINTS DE VIE DE BASE DU HERO

        int getCHp()const; //OBTENIR LES POINTS DE VIE DU HERO EN JEU
        void setCHp(int newHp); //MODIFIER LES POINTS DE VIE DU HERO EN JEU

        int getMovement()const; //OBTENIR LE NOMBRE DE MOUVEMENT MAXIMUM DU HERO
        void setMovement(int newMovement); //MODIFIER LE NOMBRE DE MOUVEMENT MAXIMUM DU HERO

        int getCMovement()const; //OBTENIR LE NOMBRE DE MOUVEMENT DU HERO EN JEU
        void setCMovement(int newCMovement); //OBTENIR LE NOMBRE DE MOUVEMENT DU HERO EN JEU
        void resetCMovement(); //REMETTRE LE NOMBRE DE MOUVEMENT DU HERO AU NOMBRE DE BASE
        bool getAlreadyPlayed();
        void setAlreadyPlayed(bool play);

        Spell* getSpell(int numero)const; //OBTENIR UN SORT DANS LA LISTE PAR APPORT A SON EMPLACEMENT DANS CELLE CI
        vector<Spell*>& getSpells(); //OBTENIR TOUT LES SORTS DE LA LISTE
};

#endif // HERO_H
