#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Boundary.h"
#include <SFML/Graphics/Rect.hpp>
#include "Player2.h"
#include "Player.h"
#include "Pickup.h"
#include "AISnake.h"

GameManager::GameManager()
{
    //ctor
    collectables.resize(5); //sets the size of the collectables vector to 5
}

GameManager::~GameManager()
{
    //dtor
}

void GameManager::SnakeAgainstSnakeCollisionDetection(Player& HumanSnake1, Player2& HumanSnake2, AISnake& ComputerBlocker)
{
    for(unsigned int i = 1; i < HumanSnake1.Segments.size(); i++) //Detects the collision of Player 1's snake against itself
    {
        sf::Vector2f quick_thing = HumanSnake1.Segments[0] - HumanSnake1.Segments[i];

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            HumanSnake1.setAlive();
        }
    }

    for(unsigned int i = 0; i < HumanSnake2.Segments.size(); i++) //Detects the collision of Player 1's snake against Player 2's snake
    {
        sf::Vector2f quick_thing = HumanSnake1.Segments[0] - HumanSnake2.Segments[i];

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            HumanSnake1.setAlive();
        }
    }

    for(unsigned int i = 1; i < HumanSnake2.Segments.size(); i++) //Detects the collision of Player 2's snake against itself
    {
        sf::Vector2f quick_thing = HumanSnake2.Segments[0] - HumanSnake2.Segments[i];

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            HumanSnake2.setAlive();
        }
    }

    for(unsigned int i = 0; i < HumanSnake1.Segments.size(); i++) //Detects the collision of Player 2's snake against Player 1's snake
    {
        sf::Vector2f quick_thing = HumanSnake2.Segments[0] - HumanSnake1.Segments[i];

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            HumanSnake2.setAlive();
        }
    }

    for(unsigned int i = 0; i < ComputerBlocker.Segments.size(); i++) //Detects the collision of Player 2's snake against the AI snake
    {
        sf::Vector2f quick_thing = HumanSnake2.Segments[0] - ComputerBlocker.Segments[i];

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            HumanSnake2.setAlive();
        }
    }

    for(unsigned int i = 0; i < ComputerBlocker.Segments.size(); i++) //Detects the collision of Player 1's snake against Player 2's snake
    {
        sf::Vector2f quick_thing = HumanSnake1.Segments[0] - ComputerBlocker.Segments[i];

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            HumanSnake1.setAlive();
        }
    }

    if(ComputerBlocker.getAlive() == true) //only checks for collisions if the AISnake is alive
    {
        for(unsigned int i = 0; i < HumanSnake1.Segments.size(); i++) //Detects the collision of Player 2's snake against Player 1's snake
        {
            sf::Vector2f quick_thing = ComputerBlocker.Segments[0] - HumanSnake1.Segments[i];

            if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
            {
                ComputerBlocker.setAlive();
                if(ComputerBlocker.getAlive() == false)
                {
                    HumanSnake1.setScore(1000);
                }
            }
        }

        for(unsigned int i = 0; i < HumanSnake2.Segments.size(); i++) //Detects the collision of Player 2's snake against Player 1's snake
        {
            sf::Vector2f quick_thing = ComputerBlocker.Segments[0] - HumanSnake2.Segments[i];

            if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
            {
                ComputerBlocker.setAlive();
                if(ComputerBlocker.getAlive() == false)
                {
                    HumanSnake2.setScore(1000);
                }
            }
        }
    }
}

void GameManager::displayTime(sf::RenderWindow& window, sf::Clock& timeClock)
{
    sf::Vector2u fSize = window.getSize(); //gets the size of the window

    std::ostringstream ss;
    ss << "Time Remaining: " << 90 - (timeClock.getElapsedTime().asMilliseconds()/1000); //outputs the time remaining of the game


    sf::Text timeText;
    sf::Font font;

    if(!font.loadFromFile("arial.ttf"))
    {
        //error
    }

    timeText.setString(ss.str());
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setColor(sf::Color::White);
    timeText.setPosition((fSize.x/2-(timeText.getGlobalBounds().width/2)),(fSize.y/20)); //sets the position according to the size of the screen, so that it 'should' work for all displays

    window.draw(timeText);
}

void GameManager::displayScore(sf::RenderWindow& window, Player& HumanSnake1)
{

    sf::Vector2u fSize = window.getSize();

    std::ostringstream hs1;

    hs1 << "Player 1: " << HumanSnake1.getScore(); //outputs Player 1's score
    sf::Text playerScoreText;
    sf::Font font;

    if(!font.loadFromFile("arial.ttf"))
    {
        //error
    }

    playerScoreText.setString(hs1.str());
    playerScoreText.setFont(font);
    playerScoreText.setCharacterSize(40);
    playerScoreText.setColor(sf::Color::Red); //sets the colour of the text to be the same as the colour of Player 1
    playerScoreText.setPosition((fSize.x/4 - (playerScoreText.getGlobalBounds().width/4)),(fSize.y/20)); //sets the position of Player 1's score to be the top left side of the screen

    window.draw(playerScoreText);
}

void GameManager::displayP2Score(sf::RenderWindow& window, Player2& HumanSnake2)
{
    sf::Vector2u fSize = window.getSize();

    std::ostringstream hs2;

    hs2 << "Player 2: " << HumanSnake2.getScore(); //outputs Player 2's score
    sf::Text player2ScoreText;
    sf::Font font;

    if(!font.loadFromFile("arial.ttf"))
    {
        //error
    }

    player2ScoreText.setString(hs2.str());
    player2ScoreText.setFont(font);
    player2ScoreText.setCharacterSize(40);
    player2ScoreText.setColor(sf::Color::Magenta); //sets the colour of the text to be the same as the colour of Player 2

    player2ScoreText.setPosition((fSize.x/4*3 - (player2ScoreText.getGlobalBounds().width/4*3)),(fSize.y/20)); //sets the position of Player 2's score to be the top left side of the screen

    window.draw(player2ScoreText);
}

void GameManager::player1Control(Player& HumanSnake1)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //If Player 1 is pressing "Up" arrow key
    {
        if(HumanSnake1.getVelocity().y != 30)
        {
            HumanSnake1.setVelocity(0,-1);
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //If Player 1 is pressing "Right" arrow key
    {
        if(HumanSnake1.getVelocity().x != -30)
        {
            HumanSnake1.setVelocity(1,0);
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //If Player 1 is pressing "Down" arrow key
    {
        if(HumanSnake1.getVelocity().y != -30)
        {
            HumanSnake1.setVelocity(0,1);
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //If Player 1 is pressing "Left" arrow key
    {
        if(HumanSnake1.getVelocity().x != 30)
        {
            HumanSnake1.setVelocity(-1,0);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) //If Player 1 is pressing "Left Shift" key
    {
        HumanSnake1.useGlue();
    }
}

void GameManager::player2Control(Player2& HumanSnake2)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //If Player 2 is pressing "Up" arrow key
    {
        if(HumanSnake2.getVelocity().y != 30)
        {
            HumanSnake2.setVelocity(0,-1);
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //If Player 2 is pressing "Right" arrow key
    {
        if(HumanSnake2.getVelocity().x != -30)
        {
            HumanSnake2.setVelocity(1,0);
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //If Player 2 is pressing "Down" arrow key
    {
        if(HumanSnake2.getVelocity().y != -30)
        {
            HumanSnake2.setVelocity(0,1);
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //If Player 2 is pressing "Left" arrow key
    {
        if(HumanSnake2.getVelocity().x != 30)
        {
            HumanSnake2.setVelocity(-1,0);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) //If Player 2 is pressing "Right Shift" key
    {
        HumanSnake2.useGlue();
    }
}

void GameManager::player1PickupCheck(Player& HumanSnake1)
{
    for(int i = 0; i < 5; i++)
    {
        sf::Vector2f quick_thing = HumanSnake1.Segments[0] - collectables[i].getPosition();

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30)) //checks using pythagoras to see if Player 1 is within the bounds of the collectable
        {
            collectables[i].setInactive();
            HumanSnake1.setScore(collectables[i].getScoreReward());

            while(collectables[i].growthAmount > 0)
            {
                HumanSnake1.Segments.push_back(sf::Vector2f(-30, -30));
                collectables[i].growthAmount--;
            }

            if(collectables[i].getGluePickup() == true)
            {
                HumanSnake1.setGlue(true);
            }
        }
    }
}

void GameManager::player2PickupCheck(Player2& HumanSnake2)
{
    for(int i = 0; i < 5; i++)
    {
        sf::Vector2f quick_thing = HumanSnake2.Segments[0] - collectables[i].getPosition();

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30)) //checks using pythagoras to see if Player 2 is within the bounds of the collectable
        {
            collectables[i].setInactive();
            HumanSnake2.setScore(collectables[i].getScoreReward());

            while(collectables[i].growthAmount > 0)
            {
                HumanSnake2.Segments.push_back(sf::Vector2f(-30, -30));
                collectables[i].growthAmount--;
            }

            if(collectables[i].getGluePickup() == true)
            {
                HumanSnake2.setGlue(true);
            }
        }
    }
}

void GameManager::AISnakePickupCheck(AISnake& ComputerBlocker)
{
    for(int i = 0; i < 5; i++)
    {
        sf::Vector2f quick_thing = ComputerBlocker.Segments[0] - collectables[i].getPosition();

        if (quick_thing.x * quick_thing.x + quick_thing.y * quick_thing.y < (30 * 30))
        {
            collectables[i].setInactive();

            while(collectables[i].growthAmount > 0)
            {
                ComputerBlocker.Segments.push_back(sf::Vector2f(-30, -30));
                collectables[i].growthAmount--;
            }
        }
    }
}

void GameManager::runGame()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "ICA Snake Game : S6021534", sf::Style::Default);

    sf::Vector2u fSize = window.getSize();

    int originX = fSize.x/8;
    int originY = fSize.y/8;

    unsigned int foregroundWidth = (fSize.x - (originX*2));
    unsigned int foregroundHeight = (fSize.y - (originY*2));

    window.setFramerateLimit(60);
    sf::RectangleShape foregroundcolour(sf::Vector2f(foregroundWidth,foregroundHeight)); //sets the rectangle for the foreground to be assigned dependent on the size of the screen
    foregroundcolour.setOrigin(foregroundWidth/2,foregroundHeight/2); //sets the origin of the rectangle
    foregroundcolour.setPosition(fSize.x/2,fSize.y/2);
    foregroundcolour.setFillColor(sf::Color::Cyan);

    sf::Clock c; //Clock for Player 1's movement
    sf::Clock s; //Clock for Player 1's movement
    sf::Clock ai; //Clock for the AI's movement
    sf::Clock timeClock; //Clock for the time
    sf::Clock spawnClock; //Clock for the pickups

    std::string result; //outputs who's won

    Boundary MapBounds;
    Player HumanSnake1;
    Player2 HumanSnake2;
    AISnake ComputerBlocker;

    sf::Text playerScoreText;
    sf::Text player2ScoreText;

    unsigned int GameState {1};

    Pickup Collectable;

    HumanSnake2.getSpeed();
    HumanSnake2.setVelocity(0.f,-1.f); //sets Player 2 to initially move upwards

    HumanSnake1.getSpeed();
    HumanSnake1.setVelocity(0.f,1.f); //sets Player 1 to initially move downwards

    ComputerBlocker.getSpeed();
    ComputerBlocker.setVelocity(0.f, -1.f); //sets the AI snake to initially move upwards

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        player1Control(HumanSnake1); //allows control of player 1
        player2Control(HumanSnake2); //allows control of player 2

        if(!HumanSnake1.getAlive() && HumanSnake2.getAlive() == true)
        {
            system("clear");
            result = "Player 2";
            std::cout << result << " is the winner with " << HumanSnake2.getScore() << "! Congratulations " << result << "!" << std::endl;
            break;
        }

        if((!HumanSnake1.usingGlue) && (c.getElapsedTime().asSeconds() > 0.5f)) //Move function for the snake. If the player isn't using glue and the time between the last movement step is
            //greater than 0.5 seconds, move.
        {
            HumanSnake1.move();
            c.restart();
        }

        if(HumanSnake1.usingGlue == true)
        {
            HumanSnake1.usingGlue = false;
            c.restart();
        }

        if(!HumanSnake2.getAlive() && HumanSnake1.getAlive() == true)
        {
            system("clear");
            result = "Player 1";
            std::cout << result << " is the winner with " << HumanSnake1.getScore() << "! Congratulations " << result << "!" << std::endl;
            break;
        }

        if((!HumanSnake2.usingGlue) && (s.getElapsedTime().asSeconds() > 0.5f)) //Move function for the snake. If the player isn't using glue and the time between the last movement step is
            //greater than 0.5 seconds, move.
        {
            HumanSnake2.move();
            s.restart();
        }

        if(HumanSnake2.usingGlue == true)
        {
            HumanSnake2.usingGlue = false;
            s.restart();
        }

        if(!HumanSnake2.getAlive() && !HumanSnake1.getAlive()) //checks for whether Player 1 and Player 2 have had a head on collision
        {
            if(HumanSnake2.getScore() > HumanSnake1.getScore()) //if player 2's score at collision is greater than player's 1 score then player 2 is the winner
            {
                system("clear");
                result = "Player 2";
                std::cout << result << " is the winner with " << HumanSnake2.getScore() << "! Congratulations " << result << "!" << std::endl;
                break;
            }
            else if(HumanSnake2.getScore() < HumanSnake1.getScore()) //if player 1's score at collision is greater than player's 2 score then player 1 is the winner
            {
                system("clear");
                result = "Player 1";
                std::cout << result << " is the winner with " << HumanSnake1.getScore() << "! Congratulations " << result << "!" << std::endl;
                break;
            }
            else if(HumanSnake2.getScore() == HumanSnake1.getScore()) //if the two Player's scores are equal, then the result is a tie
            {
                system("clear");
                std::cout << "It's a tie! What are the chances?" << std::endl;
                break;
            }
        }

        if(timeClock.getElapsedTime().asSeconds() > 90) //end the game if the time exceeds 90 seconds and check who's won
        {
            if(HumanSnake2.getScore() > HumanSnake1.getScore())
            {
                system("clear");
                result = "Player 2";
                std::cout << result << " is the winner with " << HumanSnake2.getScore() << "! Congratulations " << result << "!" << std::endl;
                break;
            }
            else if(HumanSnake2.getScore() < HumanSnake1.getScore())
            {
                system("clear");
                result = "Player 1";
                std::cout << result << " is the winner with " << HumanSnake1.getScore() << "! Congratulations " << result << "!" << std::endl;
                break;
            }
            else if(HumanSnake2.getScore() == HumanSnake1.getScore())
            {
                system("clear");
                std::cout << "It's a tie! What are the chances?" << std::endl;
                break;
            }
        }

        if((ai.getElapsedTime().asSeconds() > 0.5f)) //Move function for the AI snake. If the the time between the last movement step is greater than 0.5 seconds, move.
        {
            ComputerBlocker.move();

            if(ComputerBlocker.Segments[0].y < (fSize.y/8 + 100)) //if the snake gets to a certain position then change direction
            {
                ComputerBlocker.setVelocity(-1.f, 0.f);
            }
            if(ComputerBlocker.Segments[0].x < (fSize.x * 0.25)) //if the snake gets to a certain position then change direction
            {
                ComputerBlocker.setVelocity(0.f, 1.f);
            }
            if(ComputerBlocker.Segments[0].y > (fSize.y - originY - 150)) //if the snake gets to a certain position then change direction
            {
                ComputerBlocker.setVelocity(1.f, 0.f);
            }
            if(ComputerBlocker.Segments[0].x > (fSize.x * 0.75)) //if the snake gets to a certain position then change direction
            {
                ComputerBlocker.setVelocity(0.f, -1.f);
            }
            if(ComputerBlocker.Segments[0].x > (fSize.x * 0.75) && ComputerBlocker.Segments[0].y < (fSize.y / 8 + 100))
            {
                ComputerBlocker.setVelocity(-1.f, 0.f);
            }

            ai.restart();
        }

        window.clear(sf::Color::Blue); //clears the window and sets its colour to blue

        if(GameState == 1)
        {
            window.draw(foregroundcolour);

            MapBounds.draw(window);
            MapBounds.update(window);

            HumanSnake1.draw(window, sf::Color::Red, collectables);
            HumanSnake2.draw(window, sf::Color::Magenta, collectables);
            if(ComputerBlocker.getAlive() == true) //only draw the AI snake if it is alive
            {
                ComputerBlocker.draw(window, sf::Color::Blue, collectables);
            }

            displayTime(window,timeClock);
            displayScore(window, HumanSnake1);
            displayP2Score(window, HumanSnake2);

            if(rand() % 150 == 0) //generates a random number and if that value is 0, spawn a single collectable that isn't active
            {
                for (auto& t: collectables)
                {
                    if (!t.getActive())
                    {
                        t.Spawn(fSize.x,fSize.y, HumanSnake1, HumanSnake2);
                        break;
                    }
                }
            }

            for(int colNum = 0; colNum < 5; colNum++) //renders each collectable
            {
                if(collectables[colNum].getActive() == true)
                {
                    collectables[colNum].Render(window);
                }
            }

            player1PickupCheck(HumanSnake1);
            player2PickupCheck(HumanSnake2);
            AISnakePickupCheck(ComputerBlocker);

            SnakeAgainstSnakeCollisionDetection(HumanSnake1, HumanSnake2, ComputerBlocker);

        }
        window.display();
    }
}
