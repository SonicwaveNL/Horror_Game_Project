#include <../Headers/game.hpp>

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
};