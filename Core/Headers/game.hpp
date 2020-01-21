#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iObject.hpp>
#include <gridCell.hpp>
#include <support.hpp>
#include <action.hpp>
#include <player.hpp>

///@file

///\brief
/// Game class to present demo
template<unsigned int x, unsigned int y>
class Game {
  private:
    sf::RenderWindow window{sf::VideoMode{x, y}, "Booh - The game",
                            sf::Style::Fullscreen};
    std::vector<std::shared_ptr<IObject>> drawables;
    std::shared_ptr<Player> player;
    
    std::string cellType = "Floor";

    Action playingActions[4] = {
        Action(actionKeyword::up,
               [=]() { player->moveIfPossible(sf::Vector2f(0.f, -1.f)); }),
        Action(actionKeyword::down,
               [=]() { player->moveIfPossible(sf::Vector2f(0.f, 1.f)); }),
        Action(actionKeyword::left,
               [=]() { player->moveIfPossible(sf::Vector2f(-1.f, 0.f)); }),
        Action(actionKeyword::right,
               [=]() { player->moveIfPossible(sf::Vector2f(1.f, 0.f)); })};

    Action editorActions[6] = {
        Action(sf::Keyboard::Num1, [=]() { cellType = "Wall"; }),
        Action(sf::Keyboard::Num2, [=]() { cellType = "Switch"; }),
        Action(sf::Keyboard::Num3, [=]() { cellType = "Door"; }),
        Action(sf::Keyboard::Num4, [=]() { cellType = "Player"; }),
        Action(sf::Keyboard::Num5, [=]() { cellType = "Enemy"; }),
        Action(sf::Mouse::Button::Left, [&]() {
            sf::Vector2f mousePos =
                window.mapPixelToCoords(sf::Mouse::getPosition(window));
            int index[2] = {int(mousePos.x) % 20, int(mousePos.y) % 20};
            std::cout << "0 :  " << index[0] << "| 1 : " << index[1] << std::endl;
            std::cout << grid[index[0]][index[1]].getCellType() << std::endl;
            // grid[index[0]][index[1]].setCellType(cellType);
        })};

  public:
    ///\brief
    /// Game constructor
    ///\details
    /*Creates the 4 walls, a door and a player*/
    Game() {
        drawables.push_back(
            std::make_shared<Player>(sf::Vector2f(50.f, 50.f), drawables));
        player = std::static_pointer_cast<Player>(drawables[0]);
        grid = createGrid(window.getSize());
        std::cout << "grid size x : " << grid.size() << std::endl;
    };

    std::vector<std::vector<GridCell>> createGrid(sf::Vector2u windowSize);
    std::array<int, 2> findShapeFromMouse(sf::Vector2f mousePos);
    ///\brief
    /// Runs the game demo
    void run();
};

#endif