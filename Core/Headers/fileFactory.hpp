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
/// FileFactory class
///\details
/*s Filefactory class that can write a game state to a file and read it again*/
class FileFactory {
  private:
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
    /// writeToFile function
    ///\details
    /*writes a matrix that represents the current game state to a txt file which
     * name has to be given*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &*/
    ///@param fileName
    /*std::string*/
    void writeToFile(std::vector<std::vector<GridCell>> & matrix,
                     std::string fileName);

    ///\brief
    /// loadMatrixFromFile function
    ///\details
    /*fills the suplied matrix of std::vector<std::vector<GridCell>> with the
     * correct gridcells supllied by the given file*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &*/
    ///@param fileName
    /*std::string*/
    void loadMatrixFromFile(std::vector<std::vector<GridCell>> & matrix,
                            std::istream & file);

    ///@file
    ///\brief
    /// objectsToDrawables function
    ///\details
    /*returns a vector with drawable IObject pointers in a std::vector from a
     * given matrix*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &*/
    void objectsToDrawables(
        std::vector<std::shared_ptr<IObject>> & drawables,
        std::vector<std::vector<GridCell>> & matrix,
        std::unordered_map<objectType, std::vector<sf::Texture>> &
            loadedTextures);

    void objectsToDrawables(
        std::vector<std::shared_ptr<IObject>> & drawables,
        std::vector<GridCell> & matrix,
        std::unordered_map<objectType, std::vector<sf::Texture>> &
            loadedTextures);

    ///\brief
    /// fileToUi function
    ///\details
    /*turns te information in the given file into drawable shared pointers and
     * returns these in a vector*/
    ///@param file
    /*std::ifstream &*/

    std::vector<std::shared_ptr<UIElement>> fileToUi(std::istream & file);

    ///\brief
    /// writeInventoryToFile function
    ///\details
    /*writes the players current inventory to the inventory.txt file*/
    ///@param point
    /*int &*/
    ///@param amountPowerUps1
    /*int &*/
    ///@param amountPowerUps2
    /*int &*/
    void writeInventoryToFile(int & points, int & amountPowerups1,
                              int & amountPowerups2);

    ///\brief
    /// readInventroyFromFile function
    ///\details
    /*This function returns an array with al the current inventory information*/
    ///@return std::array<int,3>
    std::array<int, 3> readInventoryFromFile();
};
#endif