#include "fileFactory.hpp"

std::istream & operator>>(std::istream & input, sf::Vector2f & rhs) {
    char c;
    if (!(input >> c)) {
        throw UnknownTypeException("Not On Coordinate");
    }
    if (!(input >> rhs.x)) {
        throw UnknownTypeException("Not On Coordinate");
    }
    if (!(input >> c)) {
        throw UnknownTypeException("Not On Coordinate");
    }
    if (!(input >> rhs.y)) {
        throw UnknownTypeException("Not On Coordinate");
    }
    if (!(input >> c)) {
        throw UnknownTypeException("Not On Coordinate");
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
    std::vector<std::vector<GridCell>> & matrix, std::istream & file,
    std::unordered_map<objectType, std::vector<sf::Texture>> & loadedTextures) {
    std::vector<std::tuple<std::string, sf::Vector2f>> switches;
    std::vector<std::tuple<std::string, sf::Vector2f>> players;
    std::vector<std::tuple<std::string, sf::Vector2f>> doors;
    std::vector<std::tuple<std::string, sf::Vector2f>> monsters;
    std::vector<int> choices;
    sf::Vector2f position;
    std::string name;
    while (name != "END") {
        file >> name;
        if (name != "END") {
            try {
                file >> position;
            } catch (std::exception & problem) {
                problem.what();
            }
        }
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
                } else if (item.itemType == objectType::Floor){
                    matrix[position.x / PIXEL16][position.y / PIXEL16]
                        .setCellType(item.itemType, &loadedTextures[objectType::Floor][0]);
                    matrix[position.x / PIXEL16][position.y / PIXEL16]
                        .setPosition(position);
                }else if (item.itemType == objectType::Wall){
                    matrix[position.x / PIXEL16][position.y / PIXEL16]
                        .setCellType(item.itemType, &loadedTextures[objectType::Wall][0]);
                    matrix[position.x / PIXEL16][position.y / PIXEL16]
                        .setPosition(position);
                }
            }
        }
    }
    // switches kiezen en wegschrijven naar grid
    if (switches.size() <= 4 && switches.size() >= 1) {
        for (auto item : switches) {
            matrix[std::get<1>(item).x / PIXEL16][std::get<1>(item).y / PIXEL16]
                .setCellType(objectType::Switch, &loadedTextures[objectType::Switch][0]);
            matrix[std::get<1>(item).x / PIXEL16][std::get<1>(item).y / PIXEL16]
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
            matrix[std::get<1>(switches[random]).x / PIXEL16]
                  [std::get<1>(switches[random]).y / PIXEL16]
                      .setCellType(objectType::Switch);
            matrix[std::get<1>(switches[random]).x / PIXEL16]
                  [std::get<1>(switches[random]).y / PIXEL16]
                      .setPosition(std::get<1>(switches[random]));
        }
        prevChoices.clear();
    }
    // player kiezen en wegschrijven naar grid
    if (players.size() == 1) {
        matrix[std::get<1>(players[0]).x / PIXEL16]
              [std::get<1>(players[0]).y / PIXEL16]
                  .setCellType(objectType::Player, &loadedTextures[objectType::Player][0]);
        matrix[std::get<1>(players[0]).x / PIXEL16]
              [std::get<1>(players[0]).y / PIXEL16]
                  .setPosition(std::get<1>(players[0]));
    } else {
        int random = rand() % (players.size() - 1);
        matrix[std::get<1>(players[random]).x / PIXEL16]
              [std::get<1>(players[random]).y / PIXEL16]
                  .setCellType(objectType::Player, &loadedTextures[objectType::Player][0]);
        matrix[std::get<1>(players[random]).x / PIXEL16]
              [std::get<1>(players[random]).y / PIXEL16]
                  .setPosition(std::get<1>(players[random]));
    }
    // door kiezen en wegschrijven
    if (doors.size() == 1) {
        matrix[std::get<1>(doors[0]).x / PIXEL16]
              [std::get<1>(doors[0]).y / PIXEL16]
                  .setCellType(objectType::Door, &loadedTextures[objectType::Door][0]);
        matrix[std::get<1>(doors[0]).x / PIXEL16]
              [std::get<1>(doors[0]).y / PIXEL16]
                  .setPosition(std::get<1>(doors[0]));
    } else {
        int random = rand() % (doors.size() - 1);
        matrix[std::get<1>(doors[random]).x / PIXEL16]
              [std::get<1>(doors[random]).y / PIXEL16]
                  .setCellType(objectType::Door, &loadedTextures[objectType::Door][0]);
        matrix[std::get<1>(doors[random]).x / PIXEL16]
              [std::get<1>(doors[random]).y / PIXEL16]
                  .setPosition(std::get<1>(doors[random]));
    }
    // monster kiezen en wegschrijven
    if (monsters.size() == 1) {
        matrix[std::get<1>(monsters[0]).x / PIXEL16]
              [std::get<1>(monsters[0]).y / PIXEL16]
                  .setCellType(objectType::Monster, &loadedTextures[objectType::Monster][0]);
        matrix[std::get<1>(monsters[0]).x / PIXEL16]
              [std::get<1>(monsters[0]).y / PIXEL16]
                  .setPosition(std::get<1>(monsters[0]));
    } else {
        int random = rand() % (monsters.size() - 1);
        matrix[std::get<1>(monsters[random]).x / PIXEL16]
              [std::get<1>(monsters[random]).y / PIXEL16]
                  .setCellType(objectType::Monster, &loadedTextures[objectType::Monster][0]);
        matrix[std::get<1>(monsters[random]).x / PIXEL16]
              [std::get<1>(monsters[random]).y / PIXEL16]
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
                auto sharedDrawable = std::make_shared<Floor>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Floor][0]);
                item.setMyDrawable(sharedDrawable);
                drawables.push_back(sharedDrawable);
            } else if (soort == objectType::Wall) {
                auto sharedDrawable = std::make_shared<Wall>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Wall][0]);
                item.setMyDrawable(sharedDrawable);
                drawables.push_back(sharedDrawable);
            } else if (soort == objectType::Switch) {
                auto sharedDrawable = std::make_shared<Switch>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Switch][0]);
                item.setMyDrawable(sharedDrawable);
                drawables.push_back(sharedDrawable);
            } else if (soort == objectType::Door) {
                auto sharedDrawable = std::make_shared<Door>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Door][0]);
                item.setMyDrawable(sharedDrawable);
                drawables.push_back(sharedDrawable);
            } else if (soort == objectType::Player) {
                drawables.push_back(std::make_shared<Player>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Player][0]));
                auto sharedDrawable = std::make_shared<Floor>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Floor][0]);
                item.setMyDrawable(sharedDrawable);
                drawables.push_back(sharedDrawable);
            } else if (soort == objectType::Monster) {
                drawables.push_back(std::make_shared<Monster>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Monster][0]));
                auto sharedDrawable = std::make_shared<Floor>(
                    item.getPosition(), drawables,
                    &loadedTextures[objectType::Floor][0]);
                item.setMyDrawable(sharedDrawable);
                drawables.push_back(sharedDrawable);
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

    while (name != "END") {
        file >> name;
        if (name != "END") {
            file >> position;
            file >> size;
            file >> colorStringRect;
            file >> text;
            file >> colorStringLabel;
        }

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

void FileFactory::writeInventoryToFile(int & points, int & amountPowerups1,
                                       int & amountPowerups2) {
    std::ofstream file;
    file.open( "Core/Saves/inventory.txt");
    file << "POINTS " << points << "\n";
    file << "AMOUNT1 " << amountPowerups1 << "\n";
    file << "AMOUNT2 " << amountPowerups2 << "\n";
    file << "END";
    file.close();
}

std::array<int, 3> FileFactory::readInventoryFromFile(){
    int points, amount1, amount2;
    std::string item;
    std::ifstream file;
    file.open( "Core/Saves/inventory.txt");
    file >> item;
    if( item == "POINTS" ){
        file >> points;
    }
    file >> item;
    if( item == "AMOUNT1" ){
        file >> amount1;
    }
    file >> item;
    if( item == "AMOUNT2" ){
        file >> amount2;
    }
    file >> item;
    file.close();
    return {points, amount1, amount2};
}
