#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <action.hpp>
#include <gridCell.hpp>
#include <iObject.hpp>
#include <memory>
#include <monster.hpp>
#include <player.hpp>
#include <queue>
#include <support.hpp>
#include <vector>

///@file

///\brief
/// Game class to present demo
class Game {
 private:
  sf::RenderWindow window{sf::VideoMode{1920, 1080}, "Booh - The game",
                          sf::Style::Fullscreen};
  std::vector<std::shared_ptr<IObject>> drawables;
  std::shared_ptr<Player> player;
  std::shared_ptr<Monster> monster;
  std::vector<std::vector<GridCell>> grid;
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
      Action(sf::Keyboard::Num5, [=]() { cellType = "Monster"; }),
      Action(sf::Mouse::Button::Left, [&]() {
        sf::Vector2f mousePos =
            window.mapPixelToCoords(sf::Mouse::getPosition(window));
        int index[2] = {int(mousePos.x) % 20, int(mousePos.y) % 20};
        std::cout << "0 :  " << index[0] << "| 1 : " << index[1] << std::endl;
        std::cout << grid[index[0]][index[1]].getCellType() << std::endl;
        grid[index[0]][index[1]].setCellType(cellType);
      })};

 public:
  ///\brief
  /// Game constructor
  ///\details
  /*Creates the 4 walls, a door and a player*/
  Game() {
    drawables.push_back(
        std::make_shared<Player>(sf::Vector2f(50.f, 50.f), drawables));
    drawables.push_back(
        std::make_shared<Monster>(sf::Vector2f(50.f, 50.f), drawables));
    player = std::static_pointer_cast<Player>(drawables[0]);
    monster = std::static_pointer_cast<Monster>(drawables[1]);
    grid = createGrid(window.getSize());
    std::cout << "grid size x : " << grid.size() << std::endl;

    reversedBFSPathAlgorithm();
  };

  std::vector<std::vector<GridCell>> createGrid(sf::Vector2u windowSize);
  std::array<int, 2> findShapeFromMouse(sf::Vector2f mousePos);
  
  ///\brief
  ///Small Algorithm used by the Monster
  ///\details
  /*This Algorithm finds the next step/direction to go to. He does so by checking the value in all the GridCells next to the
  Monster, comparing which one is the fastest and then returning a vector which holds the direction the monster should go to.
  See the details for reversedBFSPathAlgorithm for further details on this subject.*/
  ///@return sf::Vector2f, containing the direction the Monster should move to. 
  sf::Vector2f findShortestStep();
  
  ///\brief
  ///Reversed Breath First Search Algorithm.
  ///\details
  /*This Algorithm is an implementation of the BFS algorithm. And can only be used for this game. It basically finds the shortest
  path from the player to the Monster (hence "reversed") so the Monster can then use the findShortestStep() algorithm to see
  which direction is the fastest to the player. The algorithm itterates over all cells in the grid and checks which cells are walkable
  and which ones aren't. It simultaneously checks on which cell the player is and saves that. It then checks all walkable cells from the 
  player to the monster using a queue and fills each cell with the distance from the player to that respective cell (the value). The
  algorithm does so until it finds the cell containing the monster and then ends. From that moment forward, all
  cells from the monster to the player contain a number. The monster can then use the findShortestStep() algorithm to check which
  cells around him have to lowest value, and thus which cell contains the shortest path to the player. */
  void reversedBFSPathAlgorithm();
  ///\brief
  /// Runs the game demo
  void run();
};

#endif