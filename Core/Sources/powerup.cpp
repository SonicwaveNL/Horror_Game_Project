#include <../Headers/powerup.hpp>

std::array<std::chrono::seconds, 2> powerupTimes = {std::chrono::seconds(10),
                                                    std::chrono::seconds(30)};

void Powerup::stopBuff() {
    switch (buffType) {
        case BuffType::PlayerSpeed: {
            // can be faster by giving the subvectors
            for (std::shared_ptr<IObject> obj : objects) {
                if (obj->getType() == objectType::Player) {
                    obj->setSpeed(oldValues[BuffType::PlayerSpeed]);
                }
            }
            break;
        }
        case BuffType::EnemySpeed: {
            for (std::shared_ptr<IObject> obj : objects) {
                if (obj->getType() == objectType::Monster) {
                    obj->setSpeed(oldValues[BuffType::EnemySpeed]);
                }
            }
            break;
        }
        default:
            throw UnknownTypeException(
                "Unknown powerup 'BuffType' type in Powerup::stopBuff");
    }
}

void Powerup::checkBuff() {
    if (isActive) {
        if (std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now()) >= expirationTime) {
            isActive = false;
            stopBuff();
        }
    }
}

void Powerup::buff(float magnitude) {
    if (!isActive) {
        if (amount <= 0) {
            return;
        }
        switch (buffType) {
            case BuffType::PlayerSpeed: {
                // can be faster by giving the subvectors
                expirationTime = std::chrono::system_clock::to_time_t(
                    std::chrono::system_clock::now() + powerupTimes[0]);
                for (std::shared_ptr<IObject> obj : objects) {
                    if (obj->getType() == objectType::Player) {
                        oldValues[BuffType::PlayerSpeed] = obj->getSpeed();
                        obj->setSpeed(obj->getSpeed() * magnitude);
                        isActive = true;
                        amount--;
                    }
                }
                break;
            }
            case BuffType::EnemySpeed: {
                expirationTime = std::chrono::system_clock::to_time_t(
                    std::chrono::system_clock::now() + powerupTimes[1]);
                for (std::shared_ptr<IObject> obj : objects) {
                    if (obj->getType() == objectType::Monster) {
                        oldValues[BuffType::EnemySpeed] = obj->getSpeed();
                        obj->setSpeed(0);
                        isActive = true;
                        amount--;
                    }
                }
                break;
            }
            default:

                throw UnknownTypeException(
                    "Unknown powerup 'BuffType' type in Powerup::buff");
        }
    }
    checkBuff();
    return;
}

int Powerup::getAmount() { return amount; }

void Powerup::move(sf::Vector2f direction) { return; }

void Powerup::moveIfPossible(sf::Vector2f direction) { return; }

bool Powerup::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Powerup::setPosition(sf::Vector2f direction) {
    prevPosition = iRect.getPosition();
    iRect.setPosition(iRect.getPosition());
}

void Powerup::draw(sf::RenderWindow & window) {
    window.draw(iRect);
    window.draw(sprite);
}

void Powerup::collision(IObject & obj) { return; }

sf::FloatRect Powerup::getBounds() { return iRect.getGlobalBounds(); }