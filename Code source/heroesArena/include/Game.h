#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Game
{

    protected:

    private:
        enum GameState { UNINITIALIZED, MENU, BATTLE, EXITING, ABOUT};
        static GameState stateOfGame;
    public:
        Game();
        virtual ~Game();
        void start();
        void loop();
        void setGameState(GameState newStateOfGame);
        int getStateOfGame();
};

#endif // GAME_H
