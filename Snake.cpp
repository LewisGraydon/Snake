#include "Snake.h"
#include "Boundary.h"
#include "Pickup.h"
#include "GameManager.h"

Snake::Snake()
{

}

Snake::~Snake()
{
    //dtor
}

int Snake::getSpeed()
{
    return speed;
}

void Snake::setVelocity(float x, float y) //takes two float values and sets the velocity that the snake move at by the speed of the snake multiplied by that value
{
    velocity.x = speed*x;
    velocity.y = speed*y;
}

void Snake::setGlue(bool glue)
{
    hasGlue = glue; //assigns the hasGlue variable in snake to be whatever truth value is passed in
}

bool Snake::getGlue()
{
    return hasGlue;
}

void Snake::useGlue()
{

    if(hasGlue) //use the glue for the player
    {
        usingGlue = true;
        hasGlue = false;
    }

    else
    {
        std::cout << "Out of glue, move into the glue zone to get more!" << std::endl;
    }
}

void Snake::move() //move the snake, with the body following wherever the head goes
{
    sf::Vector2f temp;
    sf::Vector2f prev(-1,-1);
    for (sf::Vector2f &i : Segments)
    {
        if (prev.x == -1 && prev.y == -1)
        {
            prev = i;
            i.x += velocity.x;
            i.y += velocity.y;
        }
        else
        {
            temp = i;
            i = prev;       //pop and push of the list
            prev = temp;
        }
    }
}

void Snake::setOrigin(float x, float y)
{
    sf::Vector2f(0.f,0.f);
}

void Snake::draw(sf::RenderWindow& window, sf::Color colour, std::vector <Pickup> &collectables)
{

    sf::Vector2u fSize = window.getSize();
    unsigned int foregroundWidth = fSize.x - (fSize.x/4);
    unsigned int foregroundHeight = fSize.y - (fSize.y/4);

    int originX = fSize.x/8;
    int originY = fSize.y/8;

    for(sf::Vector2f i: Segments) //collision detection for the snake against the boundaries
    {

        if (Segments[0].x < (originX + 10))
        {
            setAlive();
        }

        if (Segments[0].x > (originX + foregroundWidth - 30))
        {
            setAlive();
        }

        if (Segments[0].y < (originY + 10))
        {
            setAlive();
        }

        if (Segments[0].y > (originY + foregroundHeight - 30))
        {
            setAlive();
        }

        sf::CircleShape Body(15.f);
        Body.setOutlineThickness(1.f);
        Body.setOutlineColor(sf::Color::Black);
        Body.setFillColor(colour);
        Body.setPosition(i);
        window.draw(Body);

    }

}

