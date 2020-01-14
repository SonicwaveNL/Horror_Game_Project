#include "../Headers/support.hpp"

Action::Action(std::function<bool()> condition, std::function<void()> work)
    : condition(condition), work(work) {}

Action::Action(sf::Keyboard::Key key, std::function<void()> work)
    : condition([key]() -> bool { return sf::Keyboard::isKeyPressed(key); }),
      work(work) {}

Action::Action(sf::Mouse::Button button, std::function<void()> work)
    : condition(
          [button]() -> bool { return sf::Mouse::isButtonPressed(button); }),
      work(work) {}

Action::Action(std::function<void()> work)
    : condition([]() -> bool { return true; }), work(work) {}

void Action::operator()() {
    if (condition()) {
        work();
    }
}