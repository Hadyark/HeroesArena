#include "Game.h"
#include "Menu.h"
#include "Battle.h"
#include "About.h"
#include "SelectClass.h"
#include <SFML/Graphics.hpp>

const int FPS = 30; // Nombre d'images par seconde
const int resolutionX = 1280;
const int resolutionY = 720;
const int nbTileW = 32;
const int nbTileH = 18;

Game::GameState Game::stateOfGame = UNINITIALIZED;
sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Heroes Arena");
Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}
void Game::start()
{

    if (stateOfGame != UNINITIALIZED)
        return;

    stateOfGame = Game::MENU;
    // on fait tourner la boucle principale
    while (window.isOpen() && stateOfGame != Game::EXITING) {//Boucle du jeu
        loop();
    }
    window.close();
}

void Game::loop()
{
    cout<<"Debut loop / State: "<<getStateOfGame()<<endl;
    switch (stateOfGame) {
        case Game::MENU: {
            window.clear();
            Menu menu;
            switch(menu.show(window)){//en fonction du choix dans le menu change l'état du jeu
                case 1:{
                    window.clear();
                    setGameState(BATTLE);
                    break;
                }
                case 2:{
                    window.clear();
                    setGameState(ABOUT);
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }


        case Game::BATTLE: {//Lance une partie en affichant d'abord l'écran de selection
            window.clear();
            SelectClass select(resolutionX, resolutionY);
            Battle battle;
            battle.play(window,select.show(window));//select.show() retorune une vectueur <hero*> contenant les heros selectionnés & lance une partie
            setGameState(MENU);
            break;
        }
        case Game::ABOUT: {//Affiche "About"
            window.clear();
            About about;
            about.show(window);
            setGameState(MENU);
            break;
        }

        default: {
            break;
        }
    }
}

void Game::setGameState(GameState newStateOfGame)//Change l'état du jeu
{

    switch (newStateOfGame) {
    case UNINITIALIZED: {
        Game::stateOfGame = UNINITIALIZED;
        break;
    }
    case MENU: {
        Game::stateOfGame = MENU;cout<<"setGameState(MENU)"<<endl;
        break;
    }
    case BATTLE: {
        Game::stateOfGame = BATTLE;cout<<"setGameState(BATTLE)"<<endl;
        break;
    }
    case ABOUT: {
        Game::stateOfGame = ABOUT;cout<<"setGameState(ABOUT)"<<endl;
        break;
    }

    default: {
        cout<<"setGameState(DEFAULT)"<<endl;
        break;
    }
    }
}
int Game::getStateOfGame(){
    return stateOfGame;
    }
