#include <../Headers/game.hpp>

std::vector< std::vector< GridCell >> Game::createGrid( sf::Vector2u windowSize ){
    unsigned int amountOfColumn = windowSize.x / 20;
    unsigned int amountRectRow = windowSize.y / 20;
    unsigned int amountOfRect = amountRectRow * amountOfColumn;
    float x = 0;
    float y = 0;

    std::vector< std::vector< GridCell >> shapeMatrix;

    for (size_t i = 0; i < amountOfColumn; i++){
        shapeMatrix.push_back(std::vector<GridCell>());
        int posX = (int)x / 20;
        for (size_t j = 0; j < amountRectRow; j++){
            int posY = (int)y / 20;
            y+=20;
            shapeMatrix[posX].push_back(GridCell((sf::Vector2f(x,y)), drawables));
        }
        x+=20;
        y=0;
    }
    return shapeMatrix;
}

std::array<int,2> findShapeFromMouse( sf::Vector2f mousePos ){
    int xPos = int(mousePos.x) / 20;
    int yPos = int(mousePos.y) / 20;
    std::array<int, 2> arr = {xPos, yPos};
    return arr;
}

void Game::loadSubVectors(){
    // Clear sub-vectors to make sure there are no duplicates in the sub-vectors
    characters.clear();
    winFactors.clear();
    gameObjects.clear();
    std::vector<std::shared_ptr<IObject>> monsterCache; // Cache for holding monsters that ocurred before the player object and should thus be added after the player was added to the sub-vector
    std::vector<std::shared_ptr<IObject>> switchCache;
    for(std::shared_ptr<IObject> obj : drawables){
        switch(obj->getType()){
            case IObject::Type::Player:
                if(characters.size() >= 1){
                characters[0] = obj;
                }else{
                    characters.push_back(obj);
                }
                break;
            case IObject::Type::Monster:
                if(characters.size() >= 1){
                    characters.push_back(obj);
                }else{
                    monsterCache.push_back(obj);
                }
                break;
            case IObject::Type::Switch:
                if(winFactors.size() >= 1){
                    winFactors.push_back(obj);
                }else{
                    switchCache.push_back(obj);
                }
                break;
            case IObject::Type::Door:
            if(winFactors.size() >= 1){
                winFactors[0] = obj;
            }else{
                winFactors.push_back(obj);
            }

                break;
            
            case IObject::Type::Wall:
                gameObjects.push_back(obj);
                break;
        }
    }

    // Add the monsters in cache to the character list, after player was added on index 0. If this didn't happen, throw an error
    if(monsterCache.size() >= 1){
        if(characters.size() >= 1){
            for(std::shared_ptr<IObject> obj : monsterCache){
                characters.push_back(obj);
            }
        }else{
            IException playerError("No instance of player object is present in the object list!");
            throw playerError;
        }
    }

    if(switchCache.size() >= 1){
        if(winFactors.size() >= 1){
            for(std::shared_ptr<IObject> obj : switchCache){
                winFactors.push_back(obj);
            }
        }else{
            IException mapError("No instance of door object is present in the object list!\nIs the map corrupt?");
            throw mapError;
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        for (auto & action : playingActions) {
            action();
        }

        window.clear();
        for (auto & me : drawables) {
            me->draw(window);
        }
        window.display();

        if (player->checkWin()) {
            window.close();
        }

        sf::sleep(sf::milliseconds(20));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    // while (window.isOpen()){
    //     window.clear();

    //     // //Draw the grid.
    //     for (auto & row : grid) {
    //         for (auto & me : row) {
    //             me.draw(window);
    //         }
    //     }
    //     //Do the actions.
    //     for(auto & action : playingActions){
    //         action();
    //     }

    //     //Draw window.
    //     window.display();


    //     sf::sleep(sf::milliseconds(20));
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }
    // }
};