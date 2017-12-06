#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "Pickup.h"
#include "Player.h"
#include "Player2.h"
#include "AISnake.h"

class GameManager
{
    public:
        GameManager();
        virtual ~GameManager();

        void runGame();
        void displayTime(sf::RenderWindow& window, sf::Clock& timeClock);
        void displayScore(sf::RenderWindow& window, Player& HumanSnake1);
        void displayP2Score(sf::RenderWindow& window, Player2& HumanSnake2);
        void SnakeAgainstSnakeCollisionDetection(Player& HumanSnake1, Player2& HumanSnake2, AISnake& ComputerBlocker);
        void player1Control(Player& HumanSnake1);
        void player2Control(Player2& HumanSnake2);
        void player1PickupCheck(Player& HumanSnake1);
        void player2PickupCheck(Player2& HumanSnake2);
        void AISnakePickupCheck(AISnake& ComputerBlocker);

    protected:

    private:

    std::vector<Pickup> collectables;
};

#endif // GAMEMANAGER_H
