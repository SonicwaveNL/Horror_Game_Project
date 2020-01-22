#ifndef FILEFACTORY_HPP
#define FILEFACTORY_HPP

#include <fstream>
#include <string>

#include <support.hpp>
#include <gridCell.hpp>
#include <wall.hpp>
#include <player.hpp>
#include <monster.hpp>
#include <door.hpp>

class FileFactory{
private:
    const struct { objectType itemType; std::string writeAble; }
        types[8]{
            { objectType::Abstract, "ABSTRACT" },
            { objectType::GridCell, "GRIDCELL" },
            { objectType::Floor, "FLOOR" },
            { objectType::Wall, "WALL" },
            { objectType::Switch, "SWITCH" },
            { objectType::Door, "DOOR" },
            { objectType::Player, "PLAYER" },
            { objectType::Monster, "MONSTER" }
        };
public:

    void writeToFile(std::vector<std::vector<GridCell>> & matrix, std::string fileName );

    void loadMatrixFromFile(std::vector<std::vector<GridCell>> & matrix, std::string fileName);

    std::vector<std::shared_ptr<IObject>> objectsToDrawables( std::vector<std::vector<GridCell>> & matrix );
};

#endif