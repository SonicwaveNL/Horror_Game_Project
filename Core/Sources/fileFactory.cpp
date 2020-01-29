#include "fileFactory.hpp"

std::istream& operator>>(std::istream& input, sf::Vector2f& rhs) {
  char c;
  if (!(input >> c)) {
    // throw UnknownTypeException("1");
  }
  if (c != '(') {
    // throw UnknownTypeException("2");
  }
  if (!(input >> rhs.x)) {
    // throw UnknownTypeException("3");
  }
  if (!(input >> c)) {  // adjust so only , are correct
                        // throw UnknownTypeException("4");

  } else {
    if (c != ',') {
      // throw UnknownTypeException("5");
    }
  }
  if (!(input >> rhs.y)) {
    // throw UnknownTypeException("6");
  }
  if (!(input >> c)) {
    // throw UnknownTypeException("7");
  }
  if (c != ')') {
    // throw UnknownTypeException("8");
  }
  return input;
}

void FileFactory::writeToFile(std::vector<std::vector<GridCell>>& matrix,
                              std::string fileName) {
  std::ofstream file;
  file.open(fileName);  //@TODO exception maken en testen of hij al bestaat
  for (auto& row : matrix) {
    for (auto& item : row) {
      auto itemSoort = item.getCellType();
      for (auto const& soort : types) {
        if (itemSoort == soort.itemType) {
          file << soort.writeAble << " ";
          file << "(" << item.getPosition().x << "," << item.getPosition().y
               << ")\n";
        }
      }
    }
  }
  file << "END";
  file.close();
}

void FileFactory::loadMatrixFromFile(std::vector<std::vector<GridCell>>& matrix,
                                     std::istream& file) {
  sf::Vector2f position;
  std::string name;
  while (!file.eof()) {
    file >> name;
    if (name == "END") {
      continue;
    }
    file >> position;
    for (auto& item : types) {
      if (name == item.writeAble) {
        matrix[position.x / PIXEL16][position.y / PIXEL16].setCellType(
            item.itemType);
        matrix[position.x / PIXEL16][position.y / PIXEL16].setPosition(
            position);
      }
    }
  }
}

void FileFactory::objectsToDrawables(
    std::vector<std::shared_ptr<IObject>>& drawables,
    std::vector<std::vector<GridCell>>& matrix,
    std::unordered_map<objectType, std::vector<sf::Texture>>& loadedTextures) {
  objectType soort;
  drawables.clear();
  for (auto& row : matrix) {
    for (auto& item : row) {
      soort = item.getCellType();
    if (soort == objectType::Abstract) {
      throw UnknownTypeException();
      continue;
    } else if (soort == objectType::GridCell) {
      throw UnknownTypeException();
      continue;
    } else if (soort == objectType::Floor) {
      auto sharedDrawable = std::make_shared<Floor>(
          item.getPosition(), drawables, &loadedTextures[objectType::Floor][0]);
      item.setMyDrawable(sharedDrawable);
      drawables.push_back(sharedDrawable);
    } else if (soort == objectType::Wall) {
      auto sharedDrawable = std::make_shared<Wall>(
          item.getPosition(), drawables, &loadedTextures[objectType::Wall][0]);
      item.setMyDrawable(sharedDrawable);
      drawables.push_back(sharedDrawable);
    } else if (soort == objectType::Switch) {
      auto sharedDrawable =
          std::make_shared<Switch>(item.getPosition(), drawables,
                                   &loadedTextures[objectType::Switch][0]);
      item.setMyDrawable(sharedDrawable);
      drawables.push_back(sharedDrawable);
    } else if (soort == objectType::Door) {
      auto sharedDrawable = std::make_shared<Door>(
          item.getPosition(), drawables, &loadedTextures[objectType::Door][0]);
      item.setMyDrawable(sharedDrawable);
      drawables.push_back(sharedDrawable);
    } else if (soort == objectType::Player) {
      auto sharedDrawable =
          std::make_shared<Player>(item.getPosition(), drawables,
                                   &loadedTextures[objectType::Player][0]);
      item.setMyDrawable(sharedDrawable);
      drawables.push_back(sharedDrawable);
    } else if (soort == objectType::Monster) {
      auto sharedDrawable =
          std::make_shared<Monster>(item.getPosition(), drawables,
                                    &loadedTextures[objectType::Monster][0]);
      item.setMyDrawable(sharedDrawable);
      drawables.push_back(sharedDrawable);
    }
    }
  }
}

// void FileFactory::objectsToDrawables(
//     std::vector<std::shared_ptr<IObject>>& drawables,
//     std::vector<GridCell>& matrix,
//     std::unordered_map<objectType, std::vector<sf::Texture>>& loadedTextures) {
//   objectType soort;
//   drawables.clear();
//   for (auto& item : matrix) {
//     soort = item.getCellType();
//     if (soort == objectType::Abstract) {
//       throw UnknownTypeException();
//       continue;
//     } else if (soort == objectType::GridCell) {
//       throw UnknownTypeException();
//       continue;
//     } else if (soort == objectType::Floor) {
//       auto sharedDrawable = std::make_shared<Floor>(
//           item.getPosition(), drawables, &loadedTextures[objectType::Floor][0]);
//       item.setMyDrawable(sharedDrawable);
//       drawables.push_back(sharedDrawable);
//     } else if (soort == objectType::Wall) {
//       auto sharedDrawable = std::make_shared<Wall>(
//           item.getPosition(), drawables, &loadedTextures[objectType::Wall][0]);
//       item.setMyDrawable(sharedDrawable);
//       drawables.push_back(sharedDrawable);
//     } else if (soort == objectType::Switch) {
//       auto sharedDrawable =
//           std::make_shared<Switch>(item.getPosition(), drawables,
//                                    &loadedTextures[objectType::Switch][0]);
//       item.setMyDrawable(sharedDrawable);
//       drawables.push_back(sharedDrawable);
//     } else if (soort == objectType::Door) {
//       auto sharedDrawable = std::make_shared<Door>(
//           item.getPosition(), drawables, &loadedTextures[objectType::Door][0]);
//       item.setMyDrawable(sharedDrawable);
//       drawables.push_back(sharedDrawable);
//     } else if (soort == objectType::Player) {
//       auto sharedDrawable =
//           std::make_shared<Player>(item.getPosition(), drawables,
//                                    &loadedTextures[objectType::Player][0]);
//       item.setMyDrawable(sharedDrawable);
//       drawables.push_back(sharedDrawable);
//     } else if (soort == objectType::Monster) {
//       auto sharedDrawable =
//           std::make_shared<Monster>(item.getPosition(), drawables,
//                                     &loadedTextures[objectType::Monster][0]);
//       item.setMyDrawable(sharedDrawable);
//       drawables.push_back(sharedDrawable);
//     }
//   }
// }

std::vector<std::shared_ptr<UIElement>> FileFactory::fileToUi(
    std::istream& file) {
  const struct {
    const char* name;
    sf::Color color;
  } colors[]{{"yellow", sf::Color::Yellow},
             {"red", sf::Color::Red},
             {"blue", sf::Color::Blue},
             {"black", sf::Color::Black},
             {"cyan", sf::Color::Cyan},
             {"green", sf::Color::Green},
             {"white", sf::Color::White},
             {"magenta", sf::Color::Magenta},
             {"transparent", sf::Color::Transparent}};
  std::vector<std::shared_ptr<UIElement>> returnVector;
  std::string name, text, colorStringLabel, colorStringRect;
  sf::Vector2f position, size;
  sf::Color sfColorLabel, sfColorRect;

  while (!file.eof()) {
    file >> name;
    file >> position;
    file >> size;
    file >> colorStringRect;
    file >> text;
    file >> colorStringLabel;

    if (name == "END") {
      continue;
    }

    for (auto& color : colors) {
      if (colorStringLabel == color.name) {
        sfColorLabel = color.color;
      }
      if (colorStringRect == color.name) {
        sfColorRect = color.color;
      }
    }

    if (size == sf::Vector2f(0.f, 0.f)) {
      returnVector.push_back(std::make_shared<UIElement>(
          position, text, sfColorRect, sfColorLabel));
    } else {
      returnVector.push_back(std::make_shared<UIElement>(
          position, text, sfColorRect, sfColorLabel, sfColorLabel, size));
    }
  }
  return returnVector;
}
