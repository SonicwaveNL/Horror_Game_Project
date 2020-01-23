#include <../Headers/game.hpp>

std::vector<std::vector<GridCell>> Game::createGrid(sf::Vector2u windowSize) {
  std::cout << windowSize.x << " " << windowSize.x / 20 << std::endl;
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
      shapeMatrix[posX].push_back(GridCell((sf::Vector2f(x, y)), drawables));
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
  shapeMatrix[10][10].setCellType(objectType::Wall);
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
  std::vector<int> checksToDo = {1, 2, 3, 4};
  std::vector<int> checks;
  int myXPos = 0;
  int myYPos = 0;
  int myXPosRU = 0;
  int myYPosRU = 0;
  int smallestValue = 9000000;
  sf::Vector2f moveDirection = sf::Vector2f(0, 0);

  // for (int checker : checksToDo) {
  //   int val = rand() % checksToDo.size() + 1;
  //   checks.push_back(checksToDo[val]);
  //   checksToDo.erase(checksToDo.begin() + val - 1);
  // }

  sf::Vector2f monsterPosition = monster->getPosition();
  myXPos = monsterPosition.x / 20;
  myYPos = monsterPosition.y / 20;
  myXPosRU = (monsterPosition.x + 20) / 20;
  myYPosRU = (monsterPosition.y + 20) / 20;
  grid[myXPos][myYPos].value = 5000;
  // check up
  if ((myYPos - 1) >= 0 && grid[myXPos][myYPos - 1].value <= smallestValue &&
      (myYPosRU - 1) >= 0 &&
      grid[myXPosRU][myYPosRU - 1].value <= smallestValue) {
    smallestValue = grid[myXPos][myYPos - 1].value;
    moveDirection.x = 0;
    moveDirection.y = -1;
    // std::cout << "found smaller value in upper cell " << smallestValue
    // << "\n";
  }
  // Check down
  if ((myYPos + 1) < grid[myXPos].size() &&
      grid[myXPos][myYPos + 1].value <= smallestValue &&
      (myYPosRU + 1) < grid[myXPosRU].size() &&
      grid[myXPosRU][myYPosRU + 1].value <= smallestValue) {
    smallestValue = grid[myXPos][myYPos + 1].value;
    moveDirection.x = 0;
    moveDirection.y = 1;
    // std::cout << "found smaller value in lower cell "  << smallestValue
    // <<
    // "\n";
  }
  // Check left
  if ((myXPos - 1) >= 0 && grid[myXPos - 1][myYPos].value <= smallestValue &&
      (myXPosRU - 1) >= 0 &&
      grid[myXPosRU - 1][myYPosRU].value <= smallestValue) {
    smallestValue = grid[myXPos - 1][myYPos].value;
    moveDirection.x = -1;
    moveDirection.y = 0;
    // std::cout << "found smaller value in left cell "  << smallestValue
    // <<
    // "\n";
  }
  // Check right
  if ((myXPos + 1) < grid.size() &&
      grid[myXPos + 1][myYPos].value <= smallestValue &&
      (myXPosRU + 1) < grid.size() &&
      grid[myXPosRU + 1][myYPosRU].value <= smallestValue) {
    smallestValue = grid[myXPos + 1][myYPos].value;
    moveDirection.x = 1;
    moveDirection.y = 0;
    // std::cout << "found smaller value in right cell "  << smallestValue
    // <<
    // "\n";
  }
  // std::cout << moveDirection.x << ", " << moveDirection.y << "\n";
  return moveDirection;
}

void Game::reversedBFSPathAlgorithm() {
  for (auto &item : grid) {
    for (auto &y : item) {
      if (y.isWalkable())
        y.value = 0;
      else
        y.value = 5000;
    }
  }
  std::queue<GridCell *> q;
  int xPos = player->getPosition().x / 20;
  int yPos = player->getPosition().y / 20;

  GridCell *sourcePlayer = &grid[xPos][yPos];
  bool visited[grid.size()][grid[0].size()];

  // Fill the visited array with "isWalkAble" bools
  for (int x = 0; x < grid.size(); x++) {
    for (int y = 0; y < grid[x].size(); y++) {
      visited[x][y] = !grid[x][y].isWalkable();
    }
  }

  int xPosMonster = monster->getPosition().x / 20;
  int yPosMonster = monster->getPosition().y / 20;
  GridCell *sourceMonster = &grid[xPosMonster][yPosMonster];

  q.push(sourcePlayer);
  visited[xPosMonster][yPosMonster] = true;

  while (!q.empty()) {
    GridCell *p = q.front();
    q.pop();
    xPos = p->getPosition().x / 20;
    yPos = p->getPosition().y / 20;

    if (p == sourceMonster) {
      return;
    }
    // Check upper cell
    if ((yPos - 1) >= 0 && visited[xPos][yPos - 1] == false) {
      grid[xPos][yPos - 1].value = p->value + 1;
      q.push(&grid[xPos][yPos - 1]);
      visited[xPos][yPos - 1] = true;
    }

    // Check lower cell
    if ((yPos + 1) < grid[xPos].size() && visited[xPos][yPos + 1] == false) {
      grid[xPos][yPos + 1].value = p->value + 1;
      q.push(&grid[xPos][yPos + 1]);
      visited[xPos][yPos + 1] = true;
    }

    // Check left cell
    if ((xPos - 1) >= 0 && visited[xPos - 1][yPos] == false) {
      grid[xPos - 1][yPos].value = p->value + 1;
      q.push(&grid[xPos - 1][yPos]);
      visited[xPos - 1][yPos] = true;
    }

    // Check right cell
    if ((xPos + 1) < grid.size() && visited[xPos + 1][yPos] == false) {
      grid[xPos + 1][yPos].value = p->value + 1;
      q.push(&grid[xPos + 1][yPos]);

      visited[xPos + 1][yPos] = true;
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

    monster->moveIfPossible(findShortestStep());
    pathFindCounter++;

    if (pathFindCounter == 50) {
      pathFindCounter = 0;
      reversedBFSPathAlgorithm();
    }

    // Draw the grid.
    for (auto &me : drawables) {
      me->draw(window);
    }

    // for ( auto & row : grid){
    //   for(auto & item : row){
    //     item.draw(window);
    //   }
    // }
    // Do the actions.
    for (auto &action : playingActions) {
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