#ifndef FILEFACTORY_HPP
#define FILEFACTORY_HPP

#include <fstream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <door.hpp>
#include <floor.hpp>
#include <gridCell.hpp>
#include <iException.hpp>
#include <monster.hpp>
#include <player.hpp>
#include <support.hpp>
#include <switch.hpp>
#include <uiElement.hpp>
#include <wall.hpp>

///@file
///\brief
/// FileFactory class.
///\details
/*Filefactory class that can write game data to a file and read it again*/
class FileFactory {
  private:
  ///\brief
  ///A struct containing object types.
  ///\details
  /*This struct is used to read and write objectTypes to and from files.*/
    const struct {
        objectType itemType;
        std::string writeAble;
    } types[8]{
        {objectType::Abstract, "ABSTRACT"}, {objectType::GridCell, "GRIDCELL"},
        {objectType::Floor, "FLOOR"},       {objectType::Wall, "WALL"},
        {objectType::Switch, "SWITCH"},     {objectType::Door, "DOOR"},
        {objectType::Player, "PLAYER"},     {objectType::Monster, "MONSTER"}};

  public:
    ///\brief
    /// Writes a Matrix to a .txt file.
    ///\details
    /*Writes a matrix that represents the current game state to a .txt file which
     * name has to be given*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &*/
    ///@param fileName
    /*std::string*/
    void writeToFile(std::vector<std::vector<GridCell>> & matrix,
                     std::string fileName);

    ///\brief
    ///Loads a matrix from a .txt file.
    ///\details
    /*Fills the suplied matrix of type std::vector<std::vector<GridCell>> with the
     * correct gridcells supllied by the given file*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &*/
    ///@param fileName
    /*std::string*/
    ///@param loadedTextures
    /*std::unordered_map<objectType, std::vector<sf::Texture>> &, contains the game's textures.*/
    void loadMatrixFromFile(std::vector<std::vector<GridCell>> & matrix, std::istream & file,
        std::unordered_map<objectType, std::vector<sf::Texture>> & loadedTextures);

    ///\brief
    ///Makes Drawables from GridCells.
    ///\details
    /*Returns a vector with drawable IObject pointers in a std::vector from a
     * given matrix containing GridCells.*/
    ///@param drawables
    /*std::vector<std::shared_ptr<IObject>> &, contains all the pointers to IObjects that will be drawn.*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &, contains another vector which contains the Gridcells which will be used to make the IObjects.*/
    ///@param loadedTextures
    /*std::unordered_map<objectType, std::vector<sf::Texture>> &, contains the game's textures.*/
    void objectsToDrawables(
        std::vector<std::shared_ptr<IObject>> & drawables,
        std::vector<std::vector<GridCell>> & matrix,
        std::unordered_map<objectType, std::vector<sf::Texture>> &
            loadedTextures);

    ///\brief
    ///Makes Drawables from GridCells.
    ///\details
    /*Returns a vector with drawable IObject pointers in a std::vector from a
     * given matrix containing GridCells.*/
    ///@param drawables
    /*std::vector<std::shared_ptr<IObject>> &, contains all the pointers to IObjects that will be drawn.*/
    ///@param matrix
    /*std::vector<GridCell> &, contains the Gridcells which will be used to make the IObjects.*/
    ///@param loadedTextures
    /*std::unordered_map<objectType, std::vector<sf::Texture>> &, contains the game's textures.*/
    void objectsToDrawables(
        std::vector<std::shared_ptr<IObject>> & drawables,
        std::vector<GridCell> & matrix,
        std::unordered_map<objectType, std::vector<sf::Texture>> &
            loadedTextures);

    ///\brief
    ///Loads the UI Elements from a .txt file.
    ///\details
    /*Turns te information in the given file into drawable shared pointers and
     * returns these in a vector.*/
    ///@param file
    /*std::ifstream &, the istream from which the UI Elements will be read.*/
    std::vector<std::shared_ptr<UIElement>> fileToUi(std::istream & file);

    ///\brief
    ///Writes the state of the player inventory to a .txt file.
    ///@param point
    /*int &, the amount of points the player has.*/
    ///@param amountPowerUps1
    /*int &, the amound of powerups the player has of type 1.*/
    ///@param amountPowerUps2
    /*int &, the amound of powerups the player has of type 2.*/
    void writeInventoryToFile(int & points, int & amountPowerups1,
                              int & amountPowerups2);

    ///\brief
    ///Reads the inventory from a .txt file.
    ///\details
    /*This function returns an array with al the current inventory information*/
    ///@return std::array<int,3>
    std::array<int, 3> readInventoryFromFile();
};
#endif