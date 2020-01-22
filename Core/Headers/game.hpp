#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <action.hpp>
#include <gridCell.hpp>
#include <iObject.hpp>
#include <memory>
#include <monster.hpp>
#include <player.hpp>
#include <switch.hpp>
#include <IException.hpp>
#include <queue>
#include <support.hpp>
#include <vector>
#include <fileFactory.hpp>

///@file

///\brief
/// Game class to present demo
class Game {
  private:
    sf::RenderWindow window{sf::VideoMode{1920, 1080}, "Booh - The game",
                            sf::Style::Fullscreen};
    std::vector<std::shared_ptr<IObject>> drawables;

    std::vector<std::shared_ptr<IObject>> characters;
    std::vector<std::shared_ptr<IObject>> winFactors;
    std::vector<std::shared_ptr<IObject>> gameObjects;

    std::shared_ptr<Monster> monster;
    std::shared_ptr<Player> player;
    std::vector<std::vector<GridCell>> grid;
    objectType cellType = objectType::Floor;

    Action playingActions[5] = {
        Action(actionKeyword::up,
               [=]() { player->moveIfPossible(sf::Vector2f(0.f, -1.f)); }),
        Action(actionKeyword::down,
               [=]() { player->moveIfPossible(sf::Vector2f(0.f, 1.f)); }),
        Action(actionKeyword::left,
               [=]() { player->moveIfPossible(sf::Vector2f(-1.f, 0.f)); }),
        Action(actionKeyword::right,
               [=]() { player->moveIfPossible(sf::Vector2f(1.f, 0.f)); }),
        Action(actionKeyword::action1, [=]() {
            int switchCount = 0;

            for (size_t i = 1; i < winFactors.size(); i++) {
                std::shared_ptr<Switch> s =
                    std::static_pointer_cast<Switch>(winFactors[i]);
                    s->collision(*characters[0]);

                if (s->isActive()) {
                    switchCount++;
                }
            }
            if (switchCount == winFactors.size() - 1) {
                std::shared_ptr<Door> door =
                    std::static_pointer_cast<Door>(winFactors[0]);
                door->setOpenState(true);
            }
        })};

    Action editorActions[7] = {
        Action(sf::Keyboard::Num0, [=]() { cellType = objectType::Floor; }),
        Action(sf::Keyboard::Num1, [=]() { cellType = objectType::Wall; }),
        Action(sf::Keyboard::Num2, [=]() { cellType = objectType::Switch; }),
        Action(sf::Keyboard::Num3, [=]() { cellType = objectType::Door; }),
        Action(sf::Keyboard::Num4, [=]() { cellType = objectType::Player; }),
        Action(sf::Keyboard::Num5, [=]() { cellType = objectType::Monster; }),
        Action(sf::Mouse::Button::Left, [&]() {
            sf::Vector2f mousePos =
                window.mapPixelToCoords(sf::Mouse::getPosition(window));
            int index[2] = {int(mousePos.x) / 20, int(mousePos.y) / 20};
            grid[index[0]][index[1]].setCellType(cellType);
        })};

    ///\brief
    /// Loads the objects from the 'main' vector into their appropriate
    /// sub-vectors \details
    /*It will also put them in the right places. i.e. the player will get placed
     * at index 0, monsters after that etc.*/
    void loadSubVectors();

  public:
    ///\brief
    /// Game constructor
    ///\details
    /*Loads a map into the grid.*/
    Game() {
        FileFactory fileFactory;
        grid = createGrid(window.getSize());
        fileFactory.objectsToDrawables(drawables, grid);
        loadSubVectors();
        
        player = std::static_pointer_cast<Player>(characters[0]);
        monster = std::static_pointer_cast<Monster>(characters[1]);
        // reversedBFSPathAlgorithm();
    };

    std::array<int, 2> findShapeFromMouse(sf::Vector2f mousePos);
    ///\brief
    /// Creates a matrix of GridCells.
    ///\details
    /*The created grid is based on grid cells of 20x20 pixels.*/
    ///@param windowSize
    /*windowSize is a sf::Vector2u containing the size of the sf::RenderWindow
     * window.*/
    ///@return std::vector<std::vector<GridCell>>
    std::vector<std::vector<GridCell>> createGrid(sf::Vector2u windowSize);

    ///\brief
    /// Finds the index in the grid.
    ///\details
    /*This function find the index in the grid based on a sf::Vector2f.
    The grid is based on 20x20 pixels.*/
    ///@param position
    /*position is a sf::Vector2f containing the position of which you want the
     * index in the grid.*/
    ///@return std;:array<int,2>
    std::array<int, 2> findIndexFromPosition(sf::Vector2f position);

    ///\brief
    /// Small Algorithm used by the Monster
    ///\details
    /*This Algorithm finds the next step/direction to go to. He does so by
    checking the value in all the GridCells next to the Monster, comparing which
    one is the fastest and then returning a vector which holds the direction the
    monster should go to. See the details for reversedBFSPathAlgorithm for
    further details on this subject.*/
    ///@return sf::Vector2f, containing the direction the Monster should move
    ///to.
    sf::Vector2f findShortestStep();

    ///\brief
    /// Reversed Breath First Search Algorithm.
    ///\details
    /*This Algorithm is an implementation of the BFS algorithm. And can only be
    used for this game. It basically finds the shortest path from the player to
    the Monster (hence "reversed") so the Monster can then use the
    findShortestStep() algorithm to see which direction is the fastest to the
    player. The algorithm itterates over all cells in the grid and checks which
    cells are walkable and which ones aren't. It simultaneously checks on which
    cell the player is and saves that. It then checks all walkable cells from
    the player to the monster using a queue and fills each cell with the
    distance from the player to that respective cell (the value). The algorithm
    does so until it finds the cell containing the monster and then ends. From
    that moment forward, all cells from the monster to the player contain a
    number. The monster can then use the findShortestStep() algorithm to check
    which cells around him have to lowest value, and thus which cell contains
    the shortest path to the player. */
    void reversedBFSPathAlgorithm();
    ///\brief
    /// Runs the game demo
    void run();
};

#endif