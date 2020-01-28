#include <../Headers/game.hpp>

std::vector<std::vector<GridCell>> Game::createGrid(sf::Vector2u windowSize) {
    unsigned int amountOfColumn = windowSize.x / 20;
    unsigned int amountOfRow = windowSize.y / 20;
    unsigned int amountOfRect = amountOfRow * amountOfColumn;
    float x = 0;
    float y = 0;

    std::vector<std::vector<GridCell>> shapeMatrix;

    for (size_t i = 0; i < amountOfColumn; i++) {
        shapeMatrix.push_back(std::vector<GridCell>());
        int posX = (int)x / 20;
        for (size_t j = 0; j < amountOfRow; j++) {
            int posY = (int)y / 20;
            shapeMatrix[posX].push_back(
                GridCell((sf::Vector2f(x, y)), drawables));
            if (i == 0 || i == (amountOfColumn - 1) || j == 0 ||
                j == (amountOfRow - 1)) {
                shapeMatrix[posX][posY].setCellType(objectType::Wall);
            }
            y += 20;
        }
        x += 20;
        y = 0;
    }
    // shapeMatrix[30][30].setCellType(objectType::Player);
    // shapeMatrix[20][20].setCellType(objectType::Monster);
    // shapeMatrix[10][10].setCellType(objectType::Wall);
    return shapeMatrix;
}

std::array<int, 2> findShapeFromMouse(sf::Vector2f mousePos) {
    int xPos = int(mousePos.x) / 20;
    int yPos = int(mousePos.y) / 20;
    std::array<int, 2> arr = {xPos, yPos};
    return arr;
}

void Game::loadSubVectors() {
    // Clear sub-vectors to make sure there are no duplicates in the sub-vectors
    characters.clear();
    winFactors.clear();
    gameObjects.clear();

    // Caches for objects that should be placed last in the vectors, but ocurred
    // before the objects that should be placed before it. These get placed
    // after the original ones.
    std::vector<std::shared_ptr<IObject>> monsterCache;
    std::vector<std::shared_ptr<IObject>> switchCache;

    // Loop through the objects and try to add them to their appropriate vector,
    // according to their type. Objects will get stored in the cache if they
    // ocurred before the objects that should ocur before it.
    for (std::shared_ptr<IObject> obj : drawables) {
        switch (obj->getType()) {
            case objectType::Player:
                if (characters.size() >= 1) {
                    characters[0] = obj;
                } else {
                    characters.push_back(obj);
                }
                break;
            case objectType::Monster:
                if (characters.size() >= 1) {
                    characters.push_back(obj);
                } else {
                    monsterCache.push_back(obj);
                }
                break;
            case objectType::Switch:
                if (winFactors.size() >= 1) {
                    winFactors.push_back(obj);
                } else {
                    switchCache.push_back(obj);
                }
                break;
            case objectType::Door:
                if (winFactors.size() >= 1) {
                    winFactors[0] = obj;
                } else {
                    winFactors.push_back(obj);
                }

                break;

            case objectType::Wall:
                gameObjects.push_back(obj);
                break;
        }
    }

    // Add the monsters in cache to the character list, after player was added
    // on index 0. If this didn't happen, throw an error
    if (monsterCache.size() >= 1) {
        if (characters.size() >= 1) {
            for (std::shared_ptr<IObject> obj : monsterCache) {
                characters.push_back(obj);
            }
        } else {
            LoadPlayerError mapError;
            throw mapError;
        }
    }

    if (switchCache.size() >= 1) {
        if (winFactors.size() >= 1) {
            for (std::shared_ptr<IObject> obj : switchCache) {
                winFactors.push_back(obj);
            }
        } else {
            LoadDoorError mapError;
            throw mapError;
        }
    }
}

sf::Vector2f Game::findShortestStep() {
    int64_t windowSurfaceSizeTImesTwo =
        (window.getSize().x * window.getSize().y) * 2;
    int myXPos = monster->getPosition().x / 20;
    int myYPos = monster->getPosition().y / 20;
    grid[myXPos][myYPos].value = windowSurfaceSizeTImesTwo;
    int64_t smallestValue = windowSurfaceSizeTImesTwo;
    sf::Vector2f moveDirection = sf::Vector2f(0, 0);

    // check up
    if ((myYPos - 1) >= 0 && grid[myXPos][myYPos - 1].value < smallestValue &&
        grid[myXPos][myYPos - 1].visited) {
        smallestValue = grid[myXPos][myYPos - 1].value;
        moveDirection.x = 0;
        moveDirection.y = -1;
    }
    // Check down
    if ((myYPos + 1) < grid[myXPos].size() &&
        grid[myXPos][myYPos + 1].value < smallestValue &&
        grid[myXPos][myYPos + 1].visited) {
        smallestValue = grid[myXPos][myYPos + 1].value;
        moveDirection.x = 0;
        moveDirection.y = 1;
    }
    // Check left
    if ((myXPos - 1) >= 0 && grid[myXPos - 1][myYPos].value < smallestValue &&
        grid[myXPos - 1][myYPos].visited) {
        smallestValue = grid[myXPos - 1][myYPos].value;
        moveDirection.x = -1;
        moveDirection.y = 0;
    }
    // Check right
    if ((myXPos + 1) < grid.size() &&
        grid[myXPos + 1][myYPos].value < smallestValue &&
        grid[myXPos + 1][myYPos].visited) {
        smallestValue = grid[myXPos + 1][myYPos].value;
        moveDirection.x = 1;
        moveDirection.y = 0;
    }
    return moveDirection;
}

void Game::reversedBFSPathAlgorithm() {
    int64_t windowSurfaceSizeTImesTwo =
        (window.getSize().x * window.getSize().y) * 2;

    for (auto & column : grid) {
        for (auto & cell : column) {
            if (cell.isWalkable()) {
                cell.value = 0;
                cell.visited = false;
            } else {
                cell.visited = true;
                cell.value = windowSurfaceSizeTImesTwo;
            }
        }
    }

    std::queue<GridCell *> q;
    int xPos = player->getPosition().x / 20;
    int yPos = player->getPosition().y / 20;
    GridCell * sourcePlayer = &grid[xPos][yPos];

    int xPosMonster = monster->getPosition().x / 20;
    int yPosMonster = monster->getPosition().y / 20;
    GridCell * sourceMonster = &grid[xPosMonster][yPosMonster];
    sourceMonster->value = windowSurfaceSizeTImesTwo;
    sourceMonster->visited = true;

    q.push(sourcePlayer);

    while (!q.empty()) {
        GridCell * p = q.front();
        q.pop();
        xPos = p->getPosition().x / 20;
        yPos = p->getPosition().y / 20;

        if (p == sourceMonster) {
            return;
        }

        // set upper cell
        if ((yPos - 1) >= 0 && grid[xPos][yPos - 1].visited == false) {
            grid[xPos][yPos - 1].value = p->value + 1;
            q.push(&grid[xPos][yPos - 1]);
            grid[xPos][yPos - 1].visited = true;
        }

        // set lower cell
        if ((yPos + 1) < grid[xPos].size() &&
            grid[xPos][yPos + 1].visited == false) {
            grid[xPos][yPos + 1].value = p->value + 1;
            q.push(&grid[xPos][yPos + 1]);
            grid[xPos][yPos + 1].visited = true;
        }

        // set left cell
        if ((xPos - 1) >= 0 && grid[xPos - 1][yPos].visited == false) {
            grid[xPos - 1][yPos].value = p->value + 1;
            q.push(&grid[xPos - 1][yPos]);
            grid[xPos - 1][yPos].visited = true;
        }

        // set right cell
        if ((xPos + 1) < grid.size() && grid[xPos + 1][yPos].visited == false) {
            grid[xPos + 1][yPos].value = p->value + 1;
            q.push(&grid[xPos + 1][yPos]);
            grid[xPos + 1][yPos].visited = true;
        }
    }
};

void Game::draw(std::vector<std::shared_ptr<IObject>> & drawables) {
    for (std::shared_ptr<IObject> drawable : drawables) {
        drawable->draw(window);
    }
}
void Game::draw(std::vector<std::shared_ptr<UIElement>> & uiElements) {
    for (std::shared_ptr<UIElement> uiElement : uiElements) {
        uiElement->draw(window);
    }
}

void Game::draw(std::vector<std::vector<GridCell>> & _grid) {
    for (auto & row : _grid) {
        for (auto & cell : row) {
            cell.draw(window);
        }
    }
}

void Game::run() {
    sound.playMusic();
    while (window.isOpen()) {
        window.clear();
        switch (currentState) {
            case gameState::Menu:
                draw(MenuUI);
                for (auto & ele : MenuUI) {
                    int value = 0;
                    bool visited = false;
                    if (ele->intersect(window.mapPixelToCoords(
                            sf::Mouse::getPosition(window))) &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        auto tmp = ele->getText();
                        if (tmp == "Play") {
                            currentState = gameState::SelectMap;
                            std::cout << "Play\n";
                            break;
                        } else if (tmp == "Editor") {
                            currentState = gameState::Editor;
                            std::cout << "Editor\n";
                            break;
                        } else if (tmp == "Quit") {
                            std::cout << "Quit\n";
                            currentState = gameState::Quit;
                            break;
                        }
                    }
                }
                break;

            case gameState::SelectMap:
                draw(MapSelectionUI);
                for (auto & ele : MapSelectionUI) {
                    if (ele->intersect(window.mapPixelToCoords(
                            sf::Mouse::getPosition(window))) &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (ele->getText() != "MapSelection") {
                            chosenMap = ele->getText();
                            currentState = gameState::Play;
                            break;
                        }
                    }
                }
                break;

            case gameState::Play:
                static size_t counter = 0;
                if (!loaded) {
                    std::cout << "Loaded game.\n";
                    std::ifstream file("Core/Saves/" + chosenMap);
                    if (file) {
                        for( auto & row : grid){
                            for( auto & item : row){
                                item.setCellType(objectType::Floor);
                            }
                        }
                        factory.loadMatrixFromFile(grid, file);
                    } else {
                        currentState = gameState::Menu;
                        break;
                    }
                    factory.objectsToDrawables(drawables, grid);
                    loadSubVectors();
                    player = std::static_pointer_cast<Player>(characters[0]);
                    monster = std::static_pointer_cast<Monster>(characters[1]);
                    reversedBFSPathAlgorithm();
                    loaded = true;
                }
                // show instructions once*
                draw(drawables);
                // draw(PlayUI);
                for (auto & action : playingActions) {
                    action();
                }

                if (std::fabs(monster->getPosition().x - player->getPosition().x) <= 50 ||
                    std::fabs(monster->getPosition().y - player->getPosition().y) <= 50 ) {
                        sound.setTense();
                } else {
                    sound.setNormal();
                }

                // monster movement loop
                {
                    sf::Vector2f monsterPosition = monster->getPosition();
                    int myXPos = (monsterPosition.x) / 20;
                    int myYPos = (monsterPosition.y) / 20;

                    // bool onValidWall = false;
                    if (monster->getPosition() ==
                        grid[myXPos][myYPos].getPosition()) {
                        monster->moveIfPossible(findShortestStep());
                    } else {
                        monster->moveOld();
                    }
                }
                // difficulty of the AI
                if (counter >= difficulty) {
                    reversedBFSPathAlgorithm();
                    counter = 0;
                } else {
                    counter++;
                }

                if (player->checkWin()) {
                    currentState = gameState::Menu;
                    std::cout << "You won the game!" << std::endl;
                    break;
                }

                // add actions to remove instructions
                break;

            case gameState::Editor:
                draw(grid);
                for (auto & action : editorActions) {
                    action();
                }
                break;

            case gameState::Quit:
                window.close();
                break;

            default:
                currentState = gameState::Menu;
                break;
        }

        window.display();
        sf::sleep(sf::milliseconds(20));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
};