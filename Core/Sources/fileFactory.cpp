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
                    file << soort.writeAble;
                    file << "(" << item.getPosition().x << ","
                         << item.getPosition().y << ")\n";
                }
            }
        }
    }
}

void FileFactory::loadMatrixFromFile(
    std::vector<std::vector<GridCell>> & matrix, std::string fileName) {
    std::ifstream file;
    file.open(fileName); //@TODO exception maken
    std::string tmpString;
    int xCoordinate, yCoordinate;
    char tmpChar;
    while (!EOF) {
        file >> tmpString;

        if (!(file >> tmpChar)) {
            return;
        } // spatie

        if (!(file >> tmpChar)) {
            return;
        }
        if (!(tmpChar != '(')) {
            return;
        }

        if (!(file >> xCoordinate)) {
            return;
        }

        if (!(file >> tmpChar)) {
            return;
        }
        if (!(tmpChar != ',')) {
            return;
        }

        if (!(file >> yCoordinate)) {
            return;
        }

        if (!(file >> tmpChar)) {
            return;
        }
        if (!(tmpChar != ')')) {
            return;
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