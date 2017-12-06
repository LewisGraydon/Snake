#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Boundary.h"
#include "Pickup.h"

class Snake
{
public:
    Snake();
    virtual ~Snake();

    std::vector<sf::Vector2f> Segments;

    void draw(sf::RenderWindow& window, sf::Color colour, std::vector <Pickup> &collectables);

    int getSpeed();

    void setVelocity(float x, float y);

    sf::Vector2f getVelocity()
    {
        return velocity;
    }

    void setOrigin(float x, float y);

    void setGlue(bool glue);

    void useGlue();

    bool getGlue();

    void move();

    void setAlive()
    {
        isAlive = false;
    }

    bool getAlive()
    {
        return isAlive;
    }

    bool usingGlue {false};

    int getScore()
    {
        return score;
    }

    void setScore(int scoreReward)
    {
        score += scoreReward;
    }

protected:

private:

    int score {0};
    int speed {30};
    sf::Vector2f velocity;
    bool isAlive {true};
    bool hasGlue {false};

};

#endif // SNAKE_H
