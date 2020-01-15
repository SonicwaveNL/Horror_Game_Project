#include "../Headers/support.hpp"

void Action::operator()() {
    if (condition()) {
        work();
    }
}