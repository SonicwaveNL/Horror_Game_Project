#include <../Headers/game.hpp>

std::vector< std::vector< GridCell >> Game::createGrid( sf::Vector2u windowSize ){
    unsigned int amountOfColumn = windowSize.x /20;
    unsigned int amountRectRow = windowSize.y / 20;
    unsigned int amountOfRect = amountRectRow * amountOfColumn;
    float x = 0;
    float y = 0;

    std::vector< std::vector< GridCell >> shapeMatrix;

    for( unsigned int i = 0; i < amountOfRect; i++ ){
        GridCell shape;
        shape.setPosition( sf::Vector2f(x, y) );

        int posX = (int)x % 20;
        int posY = (int)y % 20;

        shapeMatrix[posX][posY] = shape;

        if( i == (amountRectRow-1) ){
            x = 0;
            y += 20;
        } else {
            x += 20;
        }
    }
    return shapeMatrix;
}

int arr[2] findShapeFromMouse( sf::Vector2f mousePos ){
    int xPos = int(mousePos.x) / 20;
    int yPos = int(mousePos.y) / 20;
    int arr[2] = {xPos, yPos};
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

    while (window.isOpen()){
        window.clear();

        //Draw the grid.
        for (auto & row : grid) {
            for (auto & me : row) {
                me.draw(window);
            }
        }
        //Do the actions.
        for(auto & action : editorActions){
            action();
        }

        //Draw window.
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