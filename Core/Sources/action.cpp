#include "../Headers/action.hpp"


void Action::operator()() {
  if (condition()) {
    work();
  }
}