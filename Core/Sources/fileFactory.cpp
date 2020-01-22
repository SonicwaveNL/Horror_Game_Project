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
    std::string tmpCoordinates;
    while (!file.eof()) {
        std::string xCoordinate, yCoordinate;
        file >> tmpString;
        // std::cout << tmpString;
        file >> tmpCoordinates;
        bool x = true;
        for (unsigned int i = 1; i < tmpCoordinates.size() - 1; i++) {
            if (tmpCoordinates[i] != ',' && x != false) {
                xCoordinate += tmpCoordinates[i];
            }
            x = false;
            if (tmpCoordinates[i] != ',' && x == false) {
                yCoordinate += tmpCoordinates[i];
            }
        }
        // std::cout << " coordinates: " << std::atoi(xCoordinate.c_str()) <<
        // "," << std::atoi(yCoordinate.c_str()) << std::endl;
        int xCor = std::atoi(xCoordinate.c_str());
        int yCor = std::atoi(yCoordinate.c_str());

        for (auto & item : types) {
            if (tmpString == item.writeAble) {
                matrix[xCor / 20][yCor / 20].setCellType(item.itemType);
                matrix[xCor / 20][yCor / 20].setPosition(
                    sf::Vector2f(xCor, yCor));
            }
        }
    }
}

void FileFactory::objectsToDrawables(
    std::vector<std::shared_ptr<IObject>> & drawables,
    std::vector<std::vector<GridCell>> & matrix) {
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
                drawables.push_back(
                    std::make_shared<Wall>(item.getPosition(), drawables));

            } else if (soort == objectType::Switch) {
                drawables.push_back(
                    std::make_shared<Switch>(item.getPosition(), drawables));

            } else if (soort == objectType::Door) {
                drawables.push_back(
                    std::make_shared<Door>(item.getPosition(), drawables));

            } else if (soort == objectType::Player) {
                drawables.push_back(
                    std::make_shared<Player>(item.getPosition(), drawables));

            } else if (soort == objectType::Monster) {
                drawables.push_back(
                    std::make_shared<Monster>(item.getPosition(), drawables));
            }
        }
    }
}