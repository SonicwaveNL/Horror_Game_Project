#ifndef FILEFACTORY_HPP
#define FILEFACTORY_HPP

#include <fstream>
#include <string>

#include <support.hpp>
#include <gridCell.hpp>

class fileFactory{
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

    void writeToFile(std::vector<std::vector<GridCell>> & matrix, std::string fileName ){
        std::ofstream file;
        file.open(fileName); //@TODO exception maken en testen of hij al bestaat
        for( auto & row: matrix ){
            for( auto & item: row ){
                auto itemSoort = item.getCellType();
                for( auto const & soort: types ){
                    if( itemSoort == soort.itemType ){
                        file << soort.writeAble;
                        file << "(" << item.getPosition().x << "," << item.getPosition().y << ")\n";
                    }
                }
            }
        }
    }

    void loadFromFile(std::vector<std::vector<GridCell>> & matrix, std::string fileName){
        std::ifstream file;
        file.open(fileName); //@TODO exception maken
        while(!EOF){
            std::string tmp;
            tmp << file;
            
            
        }



    }
};

#endif