#ifndef GAME_HPP
#define GAME_HPP

#include <../../SFML-master/include/SFML/Graphics.hpp>
#include <IObject.hpp>
#include <support.hpp>
#include "player.hpp"
#include "vector"
#include "memory"

///@file
///\brief
///Game class to present demo
class Game {
private:
    sf::RenderWindow window{sf::VideoMode{1920, 1080}, "Booh - The game" };
    std::vector<IObject *> drawables;
    IObject* player;

    playingActions Action[] = {
        Action(actionKeyword::up        ,[&player](){player->moveIfPossible(sf::Vector2f(0.f,-1.f));}),
        Action(actionKeyword::down      ,[&player](){player->moveIfPossible(sf::Vector2f(0.f,1.f));}),
        Action(actionKeyword::left      ,[&player](){player->moveIfPossible(sf::Vector2f(-1.f,0.f))};),
        Action(actionKeyword::right     ,[&player](){player->moveIfPossible(sf::Vector2f(1.f,0.f))};)
    };

public:
    ///\brief
    ///Game constructor
    ///\details
    /*Creates the 4 walls, a door and a player*/
    Game():{
        drawables.push_back(std::make_unique<Player>(sf::Vector2f(50.f,50.f)    ,sf::Vector2f(25.f,25.f)    ,drawables));
        drawables.push_back(std::make_unique<Wall>(sf::Vector2f(0.f,0.f)        ,sf::Vector2f(20.f,1080.f)  ,drawables));
        drawables.push_back(std::make_unique<Wall>(sf::Vector2f(0.f,0.f)        ,sf::Vector2f(1920.f,20.f)  ,drawables));
        drawables.push_back(std::make_unique<Wall>(sf::Vector2f(1900.f,0.f)     ,sf::Vector2f(20.f,1080.f)  ,drawables));
        drawables.push_back(std::make_unique<Wall>(sf::Vector2f(0.f,1060.f)     ,sf::Vector2f(1920.f,20.f)  ,drawables));
        drawables.push_back(std::make_unique<Door>(sf::Vector2f(1895.f,500.f)   ,sf::Vector2f(10.f,80.f)    ,drawables));
        player = drawables[0];
    };
    ///\brief
    ///Runs the game demo
    void run();
};

#endif