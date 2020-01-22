#include "fileFactory.hpp"

void FileFactory::writeToFile(std::vector<std::vector<GridCell>> & matrix,
                              std::string fileName) {
    std::ofstream file;
    file.open(fileName); //@TODO exception maken en testen of hij al bestaat
    for (auto & row : matrix) {
        for (auto & item : row) {
            auto itemSoort = item.getCellType();
            for (auto const & soort : types) {
                if (itemSoort == soort.itemType) {
                    file << soort.writeAble << " ";
                    file << "(" << item.getPosition().x << ","
                         << item.getPosition().y << ")\n";
                }
            }
        }
    }
}

void FileFactory::loadMatrixFromFile(
    std::vector<std::vector<GridCell>> & matrix, std::ifstream & file) {
    std::string tmpString;
    int xCoordinate, yCoordinate;
    char tmpChar;
    while (!file.eof()) {
        file >> tmpString;
        std::cout << tmpString;

        if (!(file >> tmpChar)) {
            std::cout << "NO WRONG \n";
            continue;
        } // spatie


        if (!(file >> tmpChar)) {
            std::cout << "NO WRONG \n";
            continue;
        }

        if (!(tmpChar != '(')) {
            std::cout << "NO WRONG " << tmpChar <<std::endl;
            continue;
        }

        if (!(file >> xCoordinate)) {
            std::cout << "NO WRONG " << xCoordinate <<std::endl;
            continue;
        }

        if (!(file >> tmpChar)) {
            std::cout << "NO WRONG \n";
            continue;
        }

        if (!(tmpChar != ',')) {
            std::cout << "NO WRONG " << tmpChar <<std::endl;
            continue;
        }

        if (!(file >> yCoordinate)) {
            std::cout << "NO WRONG " << yCoordinate <<std::endl;
            continue;
        }

        if (!(file >> tmpChar)) {
            std::cout << "NO WRONG \n";
            continue;
        }
        if (!(tmpChar != ')')) {
            std::cout << "NO WRONG " << tmpChar <<std::endl;
            continue;
        }

        for (auto & item : types) {
            if (tmpString == item.writeAble) {
                matrix[xCoordinate / 20][yCoordinate / 20].setCellType(
                    item.itemType);
                matrix[xCoordinate / 20][yCoordinate / 20].setPosition(
                    sf::Vector2f(xCoordinate, yCoordinate));
            }
        }
    }
}

void FileFactory::objectsToDrawables(std::vector<std::shared_ptr<IObject>>&drawables, std::vector<std::vector<GridCell>> & matrix) {
    objectType soort;
    for (auto & row : matrix) {
        for (auto & item : row) {
            soort = item.getCellType();
            if (soort == objectType::Abstract) {
                // throw exception
                continue;
            } else if (soort == objectType::GridCell) {
                // throw exception
                continue;
            } else if (soort == objectType::Floor) {
                continue;
            } else if (soort == objectType::Wall) {
                drawables.push_back(std::make_shared<Wall>(item.getPosition(), drawables));

            } else if (soort == objectType::Switch) {
                drawables.push_back(std::make_shared<Switch>(item.getPosition(), drawables));

            } else if (soort == objectType::Door) {
                drawables.push_back(std::make_shared<Door>(item.getPosition(), drawables));

            } else if (soort == objectType::Player) {
                drawables.push_back(std::make_shared<Player>(item.getPosition(), drawables));

            } else if (soort == objectType::Monster) {
                drawables.push_back(std::make_shared<Monster>(item.getPosition(), drawables));
            }
        }
    }
}