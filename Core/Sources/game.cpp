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
            y += 20;
            shapeMatrix[posX].push_back(
                GridCell((sf::Vector2f(x, y)), drawables));
            if (i == 0 || i == (amountOfColumn - 1) || j == 0 ||
                j == (amountOfRow - 2)) {
                shapeMatrix[posX][posY].setCellType(objectType::Wall);
            }
        }
        x += 20;
        y = 0;
    }
    return shapeMatrix;
}

std::array<int, 2> findShapeFromMouse(sf::Vector2f mousePos) {
    int xPos = int(mousePos.x) / 20;
    int yPos = int(mousePos.y) / 20;
    std::array<int, 2> arr = {xPos, yPos};
    return arr;
}

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

    while (window.isOpen()) {
        window.clear();

        // //Draw the grid.
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