#ifndef FILEFACTORY_HPP
#define FILEFACTORY_HPP

#include <fstream>
#include <string>
#include <ostream>

#include <support.hpp>
#include <gridCell.hpp>
#include <wall.hpp>
#include <player.hpp>
#include <monster.hpp>
#include <switch.hpp>
#include <door.hpp>

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
                            std::string fileName);

    ///@file
    ///\brief
    /// objectsToDrawables function
    ///\details
    /*returns a vector with drawable IObject pointers in a std::vector from a
     * given matrix*/
    ///@param matrix
    /*std::vector<std::vector<GridCell>> &*/
    ///@return std::vector<std::shared_ptr<IObject>>
    std::vector<std::shared_ptr<IObject>>
    objectsToDrawables(std::vector<std::vector<GridCell>> & matrix);
};

#endif