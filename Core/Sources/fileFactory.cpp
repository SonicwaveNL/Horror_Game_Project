#include "fileFactory.hpp"

std::istream & operator>>(std::istream & input, sf::Vector2f & rhs) {
    char c;
    if (!(input >> c)) {
        // std::cout << "KILL ME1\n";
    }
    if (c != '(') {
        // std::cout << "KILL ME2\n";
    }
    if (!(input >> rhs.x)) {
        // std::cout << "KILL ME3\n";
    }
    if (!(input >> c)) { // adjust so only , are correct
        // std::cout << "KILL ME4\n";

    } else {
        if (c != ',') {
            // std::cout << "KILL ME5\n";
        }
    }
    if (!(input >> rhs.y)) {
        // std::cout << "KILL ME6\n";
    }
    if (!(input >> c)) {
        // std::cout << "KILL ME7\n";
    }
    if (c != ')') {
        // std::cout << "KILL ME8\n";
    }
    return input;
}

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
    file << "END";
    file.close();
}

void FileFactory::loadMatrixFromFile(
    std::vector<std::vector<GridCell>> & matrix, std::istream & file) {
    sf::Vector2f position;
    std::string name;
    while (!file.eof()) {
        file >> name;
        if (name == "END") {
            continue;
        }
        file >> position;
        for (auto & item : types) {
            if (name == item.writeAble) {
                matrix[position.x / 20][position.y / 20].setCellType(
                    item.itemType);
                matrix[position.x / 20][position.y / 20].setPosition(position);
            }
        }
    }
}

void FileFactory::objectsToDrawables(
    std::vector<std::shared_ptr<IObject>> & drawables,
    std::vector<std::vector<GridCell>> & matrix) {
    objectType soort;
    drawables.clear();
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

std::vector<std::shared_ptr<UIElement>>
FileFactory::fileToUi(std::istream & file) {
    const struct {
        const char * name;
        sf::Color color;
    } colors[]{{"yellow", sf::Color::Yellow},
               {"red", sf::Color::Red},
               {"blue", sf::Color::Blue},
               {"black", sf::Color::Black},
               {"cyan", sf::Color::Cyan},
               {"green", sf::Color::Green},
               {"white", sf::Color::White},
               {"magenta", sf::Color::Magenta},
               {"transparent", sf::Color::Transparent}};
    std::vector<std::shared_ptr<UIElement>> returnVector;
    std::string name, text, colorStringLabel, colorStringRect;
    sf::Vector2f position, size;
    sf::Color sfColorLabel, sfColorRect;

    while (!file.eof()) {
        file >> name;
        file >> position;
        file >> size;
        file >> colorStringRect;
        file >> text;
        file >> colorStringLabel;

        if (name == "END") {
            continue;
        }

        for (auto & color : colors) {
            if (colorStringLabel == color.name) {
                sfColorLabel = color.color;
            }
            if (colorStringRect == color.name) {
                sfColorRect = color.color;
            }
        }

        if (size == sf::Vector2f(0.f, 0.f)) {
            returnVector.push_back(std::make_shared<UIElement>(
                position, text, sfColorRect, sfColorLabel));
        } else {
            returnVector.push_back(std::make_shared<UIElement>(
                position, text, sfColorRect, sfColorLabel, sfColorLabel, size));
        }
    }
    return returnVector;
}
