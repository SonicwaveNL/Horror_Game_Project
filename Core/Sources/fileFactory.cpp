#include "fileFactory.hpp"

std::istream & operator>>(std::istream & input, sf::Vector2f & rhs) {
    char c;
    if (!(input >> c)) {
        // throw UnknownTypeException("1");
    }
    if (c != '(') {
        // throw UnknownTypeException("2");
    }
    if (!(input >> rhs.x)) {
        // throw UnknownTypeException("3");
    }
    if (!(input >> c)) { // adjust so only , are correct
        // throw UnknownTypeException("4");

    } else {
        if (c != ',') {
            // throw UnknownTypeException("5");
        }
    }
    if (!(input >> rhs.y)) {
        // throw UnknownTypeException("6");
    }
    if (!(input >> c)) {
        // throw UnknownTypeException("7");
    }
    if (c != ')') {
        // throw UnknownTypeException("8");
    }
    return input;
}

void FileFactory::writeToFile(std::vector<std::vector<GridCell>> & matrix,
                              std::string fileName) {
    std::ofstream file;
    file.open(fileName);
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
    std::vector<std::tuple<std::string, sf::Vector2f>> switches;
    std::vector<std::tuple<std::string, sf::Vector2f>> players;
    std::vector<std::tuple<std::string, sf::Vector2f>> doors;
    std::vector<std::tuple<std::string, sf::Vector2f>> monsters;
    std::vector<int> choices;
    sf::Vector2f position;
    std::string name;
    while (!file.eof()) {
        file >> name;
        if (name == "END") {
            continue;
        }
        file >> position;
        ;
        for (auto & item : types) {
            if (name == item.writeAble) {
                if (item.itemType == objectType::Player) {
                    players.push_back(
                        std::tuple<std::string, sf::Vector2f>(name, position));
                } else if (item.itemType == objectType::Door) {
                    doors.push_back(
                        std::tuple<std::string, sf::Vector2f>(name, position));
                } else if (item.itemType == objectType::Switch) {
                    switches.push_back(
                        std::tuple<std::string, sf::Vector2f>(name, position));
                } else if (item.itemType == objectType::Monster) {
                    monsters.push_back(
                        std::tuple<std::string, sf::Vector2f>(name, position));
                } else {
                    matrix[position.x / 20][position.y / 20].setCellType(
                        item.itemType);
                    matrix[position.x / 20][position.y / 20].setPosition(
                        position);
                }
            }
        }
    }
    // switches kiezen en wegschrijven naar grid
    if (switches.size() <= 4 && switches.size() >= 1) {
        for (auto item : switches) {
            matrix[std::get<1>(item).x / 20][std::get<1>(item).y / 20]
                .setCellType(objectType::Switch);
            matrix[std::get<1>(item).x / 20][std::get<1>(item).y / 20]
                .setPosition(std::get<1>(item));
        }
    } else {
        std::vector<int> prevChoices;
        for (int i = 0; i < 4; i++) {
            int random = rand() % (switches.size() - 1);
            while (std::find(prevChoices.begin(), prevChoices.end(), random) !=
                   prevChoices.end()) {
                random = rand() % (switches.size() - 1);
            }
            matrix[std::get<1>(switches[random]).x / 20]
                  [std::get<1>(switches[random]).y / 20]
                      .setCellType(objectType::Switch);
            matrix[std::get<1>(switches[random]).x / 20]
                  [std::get<1>(switches[random]).y / 20]
                      .setPosition(std::get<1>(switches[random]));
        }
        prevChoices.clear();
    }
    // player kiezen en wegschrijven naar grid
    if (players.size() == 1) {
        matrix[std::get<1>(players[0]).x / 20][std::get<1>(players[0]).y / 20]
            .setCellType(objectType::Player);
        matrix[std::get<1>(players[0]).x / 20][std::get<1>(players[0]).y / 20]
            .setPosition(std::get<1>(players[0]));
    } else {
        int random = rand() % (players.size() - 1);
        matrix[std::get<1>(players[random]).x / 20]
              [std::get<1>(players[random]).y / 20]
                  .setCellType(objectType::Player);
        matrix[std::get<1>(players[random]).x / 20]
              [std::get<1>(players[random]).y / 20]
                  .setPosition(std::get<1>(players[random]));
    }
    // door kiezen en wegschrijven
    if (doors.size() == 1) {
        matrix[std::get<1>(doors[0]).x / 20][std::get<1>(doors[0]).y / 20]
            .setCellType(objectType::Door);
        matrix[std::get<1>(doors[0]).x / 20][std::get<1>(doors[0]).y / 20]
            .setPosition(std::get<1>(doors[0]));
    } else {
        int random = rand() % (doors.size() - 1);
        matrix[std::get<1>(doors[random]).x / 20]
              [std::get<1>(doors[random]).y / 20]
                  .setCellType(objectType::Door);
        matrix[std::get<1>(doors[random]).x / 20]
              [std::get<1>(doors[random]).y / 20]
                  .setPosition(std::get<1>(doors[random]));
    }
    // monster kiezen en wegschrijven
    if (monsters.size() == 1) {
        matrix[std::get<1>(monsters[0]).x / 20][std::get<1>(monsters[0]).y / 20]
            .setCellType(objectType::Monster);
        matrix[std::get<1>(monsters[0]).x / 20][std::get<1>(monsters[0]).y / 20]
            .setPosition(std::get<1>(monsters[0]));
    } else {
        int random = rand() % (monsters.size() - 1);
        matrix[std::get<1>(monsters[random]).x / 20]
              [std::get<1>(monsters[random]).y / 20]
                  .setCellType(objectType::Monster);
        matrix[std::get<1>(monsters[random]).x / 20]
              [std::get<1>(monsters[random]).y / 20]
                  .setPosition(std::get<1>(monsters[random]));
    }
}

void FileFactory::objectsToDrawables(
    std::vector<std::shared_ptr<IObject>> & drawables,
    std::vector<std::vector<GridCell>> & matrix,
    std::unordered_map<objectType, std::vector<sf::Texture>> & loadedTextures) {
    objectType soort;
    drawables.clear();
    for (auto & row : matrix) {
        for (auto & item : row) {
            soort = item.getCellType();
            if (soort == objectType::Abstract) {
                throw UnknownTypeException();
                continue;
            } else if (soort == objectType::GridCell) {
                throw UnknownTypeException();
                continue;
            } else if (soort == objectType::Floor) {
                continue;
            } else if (soort == objectType::Wall) {
                drawables.push_back(std::make_shared<Wall>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Wall][0]));

            } else if (soort == objectType::Switch) {
                drawables.push_back(std::make_shared<Switch>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Switch][0]));

            } else if (soort == objectType::Door) {
                drawables.push_back(std::make_shared<Door>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Door][0]));

            } else if (soort == objectType::Player) {
                drawables.push_back(std::make_shared<Player>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Player][0]));

            } else if (soort == objectType::Monster) {
                drawables.push_back(std::make_shared<Monster>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Monster][0]));
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
