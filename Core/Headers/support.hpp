#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
// #include <dirent.h>
// #include <sys/types.h>
// #include <vector>
// #include <string>

#define PIXEL16 16

///@file

// std::vector<std::string> getMapNames(const char * path) {
//     struct dirent * entry;
//     std::vector<std::string> returnVector;
//     DIR * dir = opendir(path);

//     if (dir == NULL) {
//         return returnVector;
//     }
//     while ((entry = readdir(dir)) != NULL) {
//         std::string fileName = entry->d_name;
//         if( fileName.find(".txt") < std::string::npos &&
//         fileName.find("level") < std::string::npos ){
//             returnVector.push_back( fileName );
//         }
//     }
//     closedir(dir);
//     return returnVector;
// }

///\brief
/// Enum class that contains input types.
enum class inputType { keyboard, controller };

enum class gameState { Menu, SelectMap, Play, Editor, Quit };

enum class objectType : size_t {
    Wall,
    Floor,
    Door,
    Switch,
    Player,
    Monster,
    Abstract,
    UIElement,
    GridCell
};

enum class floorType : size_t { Default };

enum class wallType : size_t { Default };

enum class switchType : size_t { Off, On };

enum class doorType : size_t { Default };

enum class playerType : size_t {
    Side1,
    Side2,
    Side3,
    Front1,
    Front2,
    Front3,
    Back1,
    Back2,
    Back3
};

enum class monsterType : size_t {
    Side1,
    Side2,
    Side3,
    Front1,
    Front2,
    Front3,
    Back1,
    Back2,
    Back3
};

///\brief
/// Enum class that contains keywords representing actions.
enum class actionKeyword {
    escape,
    select,
    left,
    up,
    right,
    down,
    // Reserved action keywords, usage depends on game state.
    action1,
    action2,
    action3,
    action4
};

#endif