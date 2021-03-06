#include <../Headers/game.hpp>

std::vector<std::vector<GridCell>> Game::createGrid(sf::Vector2u windowSize) {
    unsigned int amountOfColumn = windowSize.x / PIXEL16;
    unsigned int amountOfRow = windowSize.y / PIXEL16;
    unsigned int amountOfRect = amountOfRow * amountOfColumn;
    float x = 0;
    float y = 0;
    std::vector<std::vector<GridCell>> shapeMatrix;

    for (size_t i = 0; i < amountOfColumn; i++) {
        shapeMatrix.push_back(std::vector<GridCell>());
        int posX = (int)x / PIXEL16;
        for (size_t j = 0; j < amountOfRow; j++) {
            int posY = (int)y / PIXEL16;
            shapeMatrix[posX].push_back(
                GridCell((sf::Vector2f(x, y)), drawables,
                         &gameTextures[objectType::Floor][0]));
            if (i == 0 || i == (amountOfColumn - 1) || j == 0 ||
                j == (amountOfRow - 1)) {
                shapeMatrix[posX][posY].setCellType(
                    objectType::Wall, &gameTextures[objectType::Wall][0]);
            }
            y += PIXEL16;
        }
        x += PIXEL16;
        y = 0;
    }
    return shapeMatrix;
}

std::array<int, 2> Game::findIndexInGrid(sf::Vector2f position) {
    int xPos = int(position.x) / PIXEL16;
    int yPos = int(position.y) / PIXEL16;
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

            default:
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
    int myXPos = monster->getPosition().x / PIXEL16;
    int myYPos = monster->getPosition().y / PIXEL16;
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
    int xPos = player->getPosition().x / PIXEL16;
    int yPos = player->getPosition().y / PIXEL16;
    GridCell * sourcePlayer = &grid[xPos][yPos];

    int xPosMonster = monster->getPosition().x / PIXEL16;
    int yPosMonster = monster->getPosition().y / PIXEL16;
    GridCell * sourceMonster = &grid[xPosMonster][yPosMonster];
    sourceMonster->value = windowSurfaceSizeTImesTwo;
    sourceMonster->visited = true;

    q.push(sourcePlayer);

    while (!q.empty()) {
        GridCell * p = q.front();
        q.pop();
        xPos = p->getPosition().x / PIXEL16;
        yPos = p->getPosition().y / PIXEL16;

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

std::vector<std::shared_ptr<IObject>> Game::lantern() {
    sf::Vector2f playerPos = player->getPosition();
    auto playerIndex = findIndexInGrid(playerPos);
    int_fast16_t gridXSize = grid.size();
    int_fast16_t gridYSize = grid[0].size();

    // X-as in grid
    int_fast16_t leftXIndex =
        std::max<int_fast16_t>(0, playerIndex[0] - (viewDistance + 1));
    int_fast16_t rightXIndex =
        std::min<int_fast16_t>(gridXSize, playerIndex[0] + (viewDistance + 1));

    // Y-as in grid
    int_fast16_t topYIndex =
        std::max<int_fast16_t>(0, playerIndex[1] - (viewDistance + 1));
    int_fast16_t bottomYIndex =
        std::min<int_fast16_t>(gridYSize, playerIndex[1] + (viewDistance + 1));

    std::vector<GridCell> vectorToCheckForType;

    for (uint x = leftXIndex; x < rightXIndex; x++) {
        for (uint y = topYIndex; y < bottomYIndex; y++) {
            vectorToCheckForType.push_back(grid[x][y]);
        }
    }
    std::set<std::shared_ptr<IObject>> setWithDrawables;
    sf::RectangleShape line(sf::Vector2f(viewDistance * PIXEL16, 1));
    line.setPosition(playerPos.x + (PIXEL16 / 2), playerPos.y + (PIXEL16 / 2));
    bool monsterFound = false;
    for (int degree = 0; degree < 360; degree += 5) {
        auto lineBounds = line.getGlobalBounds();
        for (auto & pointer : vectorToCheckForType) {
            if (lineBounds.intersects(pointer.myDrawable->getBounds()) &&
                pointer.getType() != objectType::Player &&
                pointer.getType() != objectType::Monster) {
                setWithDrawables.insert(pointer.myDrawable);
            }
        }
        if (lineBounds.intersects(monster->getBounds())) {
            monsterFound = true;
        };
        line.setRotation(degree);
    }
    std::vector<std::shared_ptr<IObject>> vectorToDraw;
    for (auto & ptr : setWithDrawables) {
        vectorToDraw.push_back(ptr);
    }
    if (monsterFound) {
        vectorToDraw.push_back(monster);
    }
    vectorToDraw.push_back(player);
    return vectorToDraw;
}

std::unordered_map<objectType, std::vector<sf::Texture>>
Game::loadTextures(std::string file, sf::Image & source) {
    std::unordered_map<objectType, std::vector<sf::Texture>> tmpCont;
    source.loadFromFile(file);
    sf::Vector2i textureSize = {PIXEL16, PIXEL16};

    const std::array<objectType, 6> objArr = {
        objectType::Wall,   objectType::Floor,  objectType::Door,
        objectType::Switch, objectType::Player, objectType::Monster};

    for (size_t i = 0; i < (source.getSize().y / PIXEL16); i++) {
        for (size_t j = 0; j < (source.getSize().x / PIXEL16); j++) {
            sf::Texture tmp;
            if (!tmp.loadFromImage(
                    source, sf::IntRect(sf::Vector2i{PIXEL16 * j, PIXEL16 * i},
                                        sf::Vector2i{PIXEL16, PIXEL16}))) {
                throw CorruptFileException();
            } else {
                tmpCont[objArr[i]].push_back(tmp);
            }
        }
    };
    return tmpCont;
}

void Game::draw(std::vector<std::shared_ptr<IObject>> & objects) {
    for (auto & object : objects) {
        object->draw(window);
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
            case gameState::Menu: {
                loaded = false;
                window.draw(menuBgSprite);
                int ppAmount = powerups[BuffType::PlayerSpeed]->getAmount();
                int peAmount = powerups[BuffType::EnemySpeed]->getAmount();
                factory.writeInventoryToFile(points, ppAmount, peAmount);
                draw(MenuUI);
                for (auto & ele : MenuUI) {
                    if (ele->getText() == "Booh") {
                        ele->setTextSize(74);
                        ele->setLabelPosition();
                    }
                    int value = 0;
                    bool visited = false;
                    if (ele->intersect(window.mapPixelToCoords(
                            sf::Mouse::getPosition(window))) &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        auto tmp = ele->getText();
                        if (tmp == "Play") {
                            currentState = gameState::SelectMap;
                            break;
                        } else if (tmp == "Editor") {
                            currentState = gameState::Editor;
                            break;
                        } else if (tmp == "Quit") {
                            currentState = gameState::Quit;
                            break;
                        } else if (tmp == "Store") {
                            currentState = gameState::Store;
                            break;
                        }
                    }
                }
                break;
            }

            case gameState::SelectMap: {
                window.draw(menuBgSprite);

                draw(MapSelectionUI);
                for (auto & ele : MapSelectionUI) {
                    if (ele->intersect(window.mapPixelToCoords(
                            sf::Mouse::getPosition(window))) &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (ele->getText() != "Menu") {
                            chosenMap = ele->getText();
                            currentState = gameState::Play;
                            break;
                        }
                        currentState = gameState::Menu;
                    }
                }
                break;
            }

            case gameState::Editor: {
                if (!loaded) {
                    grid = createGrid(window.getSize());
                    loaded = true;
                }
                window.draw(bgSprite);
                draw(grid);
                for (auto & action : editorActions) {
                    action();
                }
                break;
            }

            case gameState::Store: {
                window.draw(menuBgSprite);
                int i = 0;
                const std::string pow1 = "Player Speedup";
                const std::string exPow1 =
                    "Price: 1 coin - Speeds up the player";
                const std::string pow2 = "Monster Freezer";
                const std::string exPow2 = "Price: 2 coins - Stops the monster";
                for (auto & item : StoreUI) {
                    if (item->getText() != "Menu") {
                        item->setTextSize(22);
                        item->setLabelPosition();
                    }
                    if (i == 3) {
                        item->setText(std::to_string(points));
                    } else if (i == 4) {
                        item->setText(std::to_string(
                            powerups[BuffType::PlayerSpeed]->getAmount()));
                    } else if (i == 5) {
                        item->setText(std::to_string(
                            powerups[BuffType::EnemySpeed]->getAmount()));
                    }
                    i++;
                }
                draw(StoreUI);
                for (auto & ele : StoreUI) {
                    int value = 0;
                    bool visited = false;
                    if (ele->getText() == "PowerUp1_move_faster") {
                        ele->setText(pow1);
                        ele->setLabelPosition();
                    } else if (ele->getText() == "PowerUp2_pause_enemy") {
                        ele->setText(pow2);
                        ele->setLabelPosition();
                    } else if (ele->getText() == "P1") {
                        ele->setText(exPow1);
                        ele->setItalic();

                    } else if (ele->getText() == "P2") {
                        ele->setText(exPow2);
                        ele->setItalic();
                    }

                    if (ele->intersect(window.mapPixelToCoords(
                            sf::Mouse::getPosition(window))) &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        auto tmp = ele->getText();
                        if (tmp == pow1) {
                            if (points >= 1) {
                                int newVal = powerups[BuffType::PlayerSpeed]
                                                 ->getAmount() +
                                             1;
                                powerups[BuffType::PlayerSpeed]->setAmount(
                                    newVal);
                                points -= 1;
                                currentState = gameState::Menu;
                            }
                            break;
                        } else if (tmp == pow2) {
                            if (points >= 2) {
                                int newVal = powerups[BuffType::EnemySpeed]
                                                 ->getAmount() +
                                             1;
                                powerups[BuffType::EnemySpeed]->setAmount(
                                    newVal);
                                points -= 2;
                                currentState = gameState::Menu;
                            }
                            break;
                        } else if (tmp == "Menu") {
                            currentState = gameState::Menu;
                            break;
                        }
                    }
                }
                break;
            }

            case gameState::Play: {
                static int counter = 0;
                if (!loaded) {
                    std::ifstream file;
                    file.open("Core/Saves/" + chosenMap);
                    if (file) {
                        for (auto & row : grid) {
                            for (auto & item : row) {
                                item.setCellType(objectType::Floor);
                            }
                        }
                        factory.loadMatrixFromFile(grid, file, gameTextures);
                    } else {
                        currentState = gameState::SelectMap;
                        break;
                    }
                    factory.objectsToDrawables(drawables, grid, gameTextures);
                    loadSubVectors();
                    player = std::static_pointer_cast<Player>(characters[0]);
                    monster = std::static_pointer_cast<Monster>(characters[1]);
                    reversedBFSPathAlgorithm();
                    loaded = true;
                }

                if (chosenMap == "tutorialMap.txt") {
                    for (auto uiElement : TutorialUI) {
                        uiElement->setTextSize(25);

                        if (uiElement->getText() == "arrowKeys_to_move") {
                            uiElement->setText("Use arrow keys to move");
                        } else if (uiElement->getText() == "TAB_for_UI") {
                            uiElement->setText("Hold tab to see the switch overlay");
                        }else if (uiElement->getText() == "Flip_switches_with_H") {
                            uiElement->setText("Flip a switch with 'H'");
                        }else if (uiElement->getText() == "Flip_Four_Switches") {
                            uiElement->setText("Flip all switches to open the door");
                        }else if (uiElement->getText() == "J_For_speedbuff") {
                            uiElement->setText("Press 'j' to activate your speedbuff");
                        }else if (uiElement->getText() == "K_For_MonsterBuff") {
                            uiElement->setText("Press 'k' to active your monster");
                        }else if(uiElement->getText() == "Run_To_Win"){
                            uiElement->setText("Run away from the monster!");
                        }

                        uiElement->setLabelPosition();
                    }

                    draw(TutorialUI);
                }
                for (auto & action : playingActions) {
                    action();
                }

                for (auto & powerup : powerups) {
                    powerup.second->checkBuff();
                }

                // sound
                if (std::fabs(monster->getPosition().x -
                              player->getPosition().x) <= 50 ||
                    std::fabs(monster->getPosition().y -
                              player->getPosition().y) <= 50) {
                    sound.setTense();
                } else {
                    sound.setNormal();
                }

                // monster movement loop
                sf::Vector2f monsterPosition = monster->getPosition();
                if (monster->getPosition() == grid[monsterPosition.x / PIXEL16]
                                                  [monsterPosition.y / PIXEL16]
                                                      .getPosition()) {
                    auto monsterDirection = findShortestStep();
                    monster->moveIfPossible(monsterDirection);
                    if (monsterDirection.x > 0) {
                        monster->setTexture(
                            &gameTextures[objectType::Monster][0]);
                    } else if (monsterDirection.x < 0) {
                        monster->setTexture(
                            &gameTextures[objectType::Monster][0]);

                    } else {
                        if (monsterDirection.y > 0) {
                            monster->setTexture(
                                &gameTextures[objectType::Monster][3]);

                        } else if (monsterDirection.y < 0) {
                            monster->setTexture(
                                &gameTextures[objectType::Monster][6]);
                        }
                    }

                } else {
                    monster->moveOld();
                }

                // difficulty of the AI
                if (counter >= difficulty) {
                    reversedBFSPathAlgorithm();
                    counter = 0;
                } else {
                    counter++;
                }

                if (player->checkWin()) {
                    points += 1;
                    currentState = gameState::WinState;
                    break;
                } else if (player->checkLose()) {
                    currentState = gameState::LoseState;
                    break;
                }

                auto a = lantern();
                draw(a);

                break;
            }
            case gameState::Quit: {
                window.close();
                break;
            }
            case gameState::WinState: {
                static int counter = 0;
                const int countMax = 400;

                auto tmp = *winloseUI[0];
                auto tmp_button = std::make_shared<UIElement>(tmp);

                sf::Font winFont;
                winFont.loadFromFile("Resources/winlose.ttf");

                tmp_button->setFont(&winFont);
                tmp_button->setText("YOU WON!");
                tmp_button->setTextSize(100);
                tmp_button->setPosition({(window.getSize().x / 2 -
                                          tmp_button->getBounds().width / 2),
                                         (window.getSize().y / 2 -
                                          tmp_button->getBounds().height / 2)});
                std::vector<std::shared_ptr<UIElement>> tmp_vector = {
                    tmp_button};
                window.draw(winBgSprite);
                draw(tmp_vector);
                counter++;

                if (counter == countMax) {
                    currentState = gameState::Menu;
                    player->reset();
                    counter = 0;
                }
                break;
            }
            case gameState::LoseState: {
                static int counter = 0;
                const int countMax = 400;

                auto tmp = *winloseUI[0];
                auto tmp_button = std::make_shared<UIElement>(tmp);

                sf::Font winFont;
                winFont.loadFromFile("Resources/winlose.ttf");

                tmp_button->setFont(&winFont);
                tmp_button->setText("YOU LOST!");
                tmp_button->setTextSize(100);
                tmp_button->setPosition({(window.getSize().x / 2 -
                                          tmp_button->getBounds().width / 2),
                                         (window.getSize().y / 2 -
                                          tmp_button->getBounds().height / 2)});
                std::vector<std::shared_ptr<UIElement>> tmp_vector = {
                    tmp_button};
                window.draw(loseBgSprite);
                draw(tmp_vector);
                counter++;

                if (counter == countMax) {
                    currentState = gameState::Menu;
                    player->reset();
                    counter = 0;
                }
                break;
            }
            default: {
                currentState = gameState::Menu;
                break;
            }
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