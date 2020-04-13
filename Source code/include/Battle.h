#ifndef BATTLE_H
#define BATTLE_H
#include <SFML/Graphics.hpp>
#include "DisplayedObject.h"
#include "Hero.h"
#include "Team.h"

class Battle
{
    public:
        Battle();
        virtual ~Battle();
        void play(sf::RenderWindow &window,vector<Hero*> heros);
        void buildBattle(vector<Hero*> heros);
        void drawMap(sf::RenderWindow& window);
        void nextRound();
        int selectHero(sf::Event event, Team* team);
        void deselectHero();
        void moveHero(sf::Event event);
        Spell* prepareSpell(sf::Event event);
        void castSpell(sf::Event event, Spell* spell);
        bool checkEndGame();
    protected:

    private:
        Team teamBlue;
        Team teamRed;
        Team* currentTeam;//Equipe qui joue à ce tour
        sf::Color stateTeam;//Couleur de l'équipe qui joue
};

#endif // BATTLE_H
