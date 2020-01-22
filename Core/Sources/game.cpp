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
    shapeMatrix[30][30].setCellType(objectType::Player);
    shapeMatrix[20][20].setCellType(objectType::Monster);
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
                std::cout << "loading subvectors\n";

    // Caches for objects that should be placed last in the vectors, but ocurred
    // before the objects that should be placed before it. These get placed
    // after the original ones.
    std::vector<std::shared_ptr<IObject>> monsterCache;
    std::vector<std::shared_ptr<IObject>> switchCache;
                std::cout << "created cache\n";

    // Loop through the objects and try to add them to their appropriate vector,
    // according to their type. Objects will get stored in the cache if they
    // ocurred before the objects that should ocur before it.
    for (std::shared_ptr<IObject> obj : drawables) {
        switch (obj->getType()) {
            case objectType::Player:
                std::cout << "Adding Player\n";
                if (characters.size() >= 1) {
                    characters[0] = obj;
                } else {
                    characters.push_back(obj);
                }
                break;
            case objectType::Monster:
                            std::cout << "Adding MOnster\n";

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
    int myXPos = 0;
    int myYPos = 0;
    int smallestValue = 999;
    sf::Vector2f moveDirection = sf::Vector2f(0, 0);

    sf::Vector2f monsterPosition = monster->getPosition();
    myXPos = monsterPosition.x / 20;
    myYPos = monsterPosition.y / 20;

    // Check up
    if ((myYPos - 1) >= 0 && grid[myYPos - 1][myXPos].value <= smallestValue) {
        smallestValue = grid[myYPos - 1][myXPos].value;
        moveDirection.x = 0;
        moveDirection.y = -1;
    }

    // Check down
    if ((myYPos + 1) < grid.size() &&
        grid[myYPos + 1][myXPos].value <= smallestValue) {
        smallestValue = grid[myYPos + 1][myXPos].value;
        moveDirection.x = 0;
        moveDirection.y = 1;
    }

    // Check left
    if ((myXPos - 1) >= 0 && grid[myYPos][myXPos - 1].value <= smallestValue) {
        smallestValue = grid[myYPos][myXPos - 1].value;
        moveDirection.x = -1;
        moveDirection.y = 0;
    }

    // Check right
    if ((myXPos + 1) < grid[myYPos].size() &&
        grid[myYPos][myXPos + 1].value <= smallestValue) {
        smallestValue = grid[myYPos][myXPos + 1].value;
        moveDirection.x = 1;
        moveDirection.y = 0;
    }

    return moveDirection;
};

void Game::reversedBFSPathAlgorithm() {
    std::queue<GridCell *> q;
    int xPos = player->getPosition().x / 20;
    int yPos = player->getPosition().y / 20;

    GridCell * source = &grid[yPos][xPos];
    bool visited[grid.size()][grid[0].size()];

    // Fill the visited array with "isWalkAble" bools
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            visited[y][x] = !grid[y][x].isWalkAble;
        }
    }

    int xPosMonster = monster->getPosition().x / 20;
    int yPosMonster = monster->getPosition().y / 20;
    GridCell * sourceMonster = &grid[yPosMonster][xPosMonster];

    q.push(source);
    visited[yPosMonster][xPosMonster] = true;

    while (!q.empty()) {
        GridCell * p = q.front();
        q.pop();

        if (p == sourceMonster) {
            return;
        }

        // Check upper cell
        if ((yPos - 1) >= 0 && visited[yPos - 1][xPos] == false) {
            grid[yPos - 1][xPos].value = p->value + 1;
            q.push(&grid[yPos - 1][xPos]);
            visited[yPos - 1][xPos] = true;
        }

        // Check lower cell
        if ((yPos + 1) < grid.size() && visited[yPos + 1][xPos] == false) {
            grid[yPos + 1][xPos].value = p->value + 1;
            q.push(&grid[yPos + 1][xPos]);
            visited[yPos + 1][xPos] = true;
        }

        // Check left cell
        if ((xPos - 1) >= 0 && visited[yPos][xPos - 1] == false) {
            grid[yPos][xPos - 1].value = p->value + 1;
            q.push(&grid[yPos][xPos - 1]);
            visited[yPos][xPos - 1] = true;
        }

        // Check right cell
        if ((xPos + 1) < grid[yPos].size() &&
            visited[yPos][xPos + 1] == false) {
            grid[yPos][xPos + 1].value = p->value + 1;
            q.push(&grid[yPos][xPos + 1]);
            visited[yPos][xPos + 1] = true;
        }
    }
};

void Game::run() {
    // while (window.isOpen()) {
    //     for (auto & action : playingActions) {
    //         action();
    //     }

    //     window.clear();
    //     for (auto & me : drawables) {
    //         me->draw(window);
    //     }
    //     window.display();

    //     if (player->checkWin()) {
    //         window.close();
    //     }

    //     sf::sleep(sf::milliseconds(20));

    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }
    // }

    int pathFindCounter = 0;

    while (window.isOpen()) {
        window.clear();

        // monster->move(findShortestStep());
        pathFindCounter++;

        if (pathFindCounter == 50) {
            pathFindCounter = 0;
            // reversedBFSPathAlgorithm();
        }

        ////Draw the grid.
        for (auto & row : grid) {
            for (auto & me : row) {
                me.draw(window);
            }
        }
        // Do the actions.
        for (auto & action : editorActions) {
            action();
        }

        // Draw window.
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