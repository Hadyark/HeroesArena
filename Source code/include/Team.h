#ifndef TEAM_H
#define TEAM_H
#include "Hero.h"
#include <string>
using namespace std;


class Team
{
    private:
        vector <Hero*> heros; //LISTE DES HEROS
        sf::Color color; //COULEUR DE LA TEAM

    public:
        //FORME CANONIQUE
        Team();//CONSTRUCTEUR
        virtual ~Team();//DESTRUCTEUR
        Team(const Team& other); //CONCTRUCTEUR DE COPIE
        Team& operator=(const Team& rhs); //OPERATEUR D'AFFECTATION

        //CRUD DES HEROS
        void addHero(Hero* r); //AJOUTER UN HERO A LA LISTE
        void removeHero(Hero& r); //SUPPRIMER UN HERO DE LA LISTE

        //AUTRES
        virtual string str()const; //AFFICHAGE

        //GETTERS ET SETTERS
        vector<Hero*> getHero()const;
        Hero* getHeroByIndex(int i)const;
        int getSizeHeroList()const;

        void setColor(sf::Color c);
        sf::Color getColor()const;
};

#endif // TEAM_H
