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
class Game {
  private:
    sf::RenderWindow window{sf::VideoMode{1920, 1080}, "Booh - The game",
                            sf::Style::Fullscreen};
    std::vector<std::shared_ptr<IObject>> drawables;
    std::shared_ptr<Player> player;
    std::vector<std::vector<GridCell>> grid;
    objectType cellType = objectType::Floor;

    Action playingActions[4] = {
        Action(actionKeyword::up,
               [=]() { player->moveIfPossible(sf::Vector2f(0.f, -1.f)); }),
        Action(actionKeyword::down,
               [=]() { player->moveIfPossible(sf::Vector2f(0.f, 1.f)); }),
        Action(actionKeyword::left,
               [=]() { player->moveIfPossible(sf::Vector2f(-1.f, 0.f)); }),
        Action(actionKeyword::right,
               [=]() { player->moveIfPossible(sf::Vector2f(1.f, 0.f)); })};

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
            int index[2] = {int(mousePos.x) / 20, int(mousePos.y) / 20 - 1};
            grid[index[0]][index[1]].setCellType(cellType);
        })};

  public:
    ///\brief
    /// Game constructor
    ///\details
    /*Loads a map into the grid.*/
    Game() {
        drawables.push_back(std::make_shared<Player>(
            sf::Vector2f(50.f, 50.f),
            drawables)); // the file will have a player already so don't do
                         // this! otherwise we have 2 players.
        player = std::static_pointer_cast<Player>(drawables[0]); // ^
        grid = createGrid(window.getSize()); // load from file
    };

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
    /// Runs the game demo
    void run();
};

#endif