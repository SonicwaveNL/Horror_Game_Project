#ifndef GAME_HPP
#define GAME_HPP

#include <sound.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/filesystem>
#include <unordered_map>
#include <action.hpp>
#include <fileFactory.hpp>
#include <gridCell.hpp>
#include <iObject.hpp>
#include <floor.hpp>
#include <memory>
#include <monster.hpp>
#include <player.hpp>
#include <switch.hpp>
#include <iException.hpp>
#include <queue>
#include <support.hpp>
#include <switch.hpp>
#include <vector>
#include <math.h>
#include <uiElement.hpp>
#include <powerup.hpp>

///@file

///\brief
/// Game class, this class runs the entire game with the run function()
class Game {
  private:
    // Defines the difficulty of the game, it dictates how often the AI is going
    // to recalculate the fastest route the the player.
    int difficulty = 50;
    int viewDistance = 5;
    int points, doorCounter, playerCounter, monsterCounter, switchCounter;

    bool loaded = false;

    sf::RenderWindow window{sf::VideoMode{1920, 1080}, "Booh - The game",
                            sf::Style::Fullscreen};

    sf::Vector2u windowSize;

    FileFactory factory;
    Sound sound;

    /*Contains the textures for the game. The tileset has to follow these rules:
        - Every tile has to be 16x16 pixels.
        - From top to bottom: Wall, Floor, Door, Switch, Player, Monster*/
    std::unordered_map<objectType, std::vector<sf::Texture>> gameTextures;
    sf::Image textureSource, bgSource, loseBgSource, winBgSource, menuSource;
    sf::Texture bgTexture, loseBgTexture, winBgTexture, menuBgTexture;
    sf::Sprite bgSprite, loseBgSprite, winBgSprite, menuBgSprite;

    std::vector<std::vector<GridCell>> grid;

    /*The drawables contains all the IObjects that we want to draw.
        The characters, winFactors and gameObjects containg a small portion of
        drawables so we can access them more easily.*/
    std::vector<std::shared_ptr<IObject>> drawables;
    std::vector<std::shared_ptr<IObject>> characters;
    std::vector<std::shared_ptr<IObject>> winFactors;
    std::vector<std::shared_ptr<IObject>> gameObjects;

    /*Also have their own variables for ease of, and faster, access*/
    std::shared_ptr<Monster> monster;
    std::shared_ptr<Player> player;

    std::vector<std::shared_ptr<UIElement>> MenuUI, MapSelectionUI, TutorialUI,
        PlayUI, EditorUI, winloseUI, StoreUI;

    std::unordered_map<BuffType, std::shared_ptr<Powerup>> powerups;

    objectType cellType = objectType::Floor;
    gameState currentState = gameState::Menu;

    std::string chosenMap = "custom.txt";
    std::string textureFile = "boohTileset.png";

    /*playingActions contain all of the actions we monitor during the Play
     * state.*/
    Action playingActions[9] = {
        Action(sf::Keyboard::Tab,
               [=]() {
                   int switchCount = 0;

                   for (size_t i = 1; i < winFactors.size(); i++) {
                       std::shared_ptr<Switch> s =
                           std::static_pointer_cast<Switch>(winFactors[i]);
                       s->collision(*characters[0]);

                       if (s->isActive()) {
                           switchCount++;
                       }
                   }
                   int counter = 0;
                   for (auto & item : PlayUI) {
                       if (switchCount >= 0) {
                           item->setText("*");
                       }
                       if (counter < winFactors.size()) {
                           item->draw(window);
                       }
                       counter++;
                       switchCount--;
                   }
               }),
        Action(actionKeyword::up,
               [=]() {
                   player->moveIfPossible(sf::Vector2f(0.f, -1.f));
                   player->setTexture(&gameTextures[objectType::Player][6]);
               }),
        Action(actionKeyword::down,
               [=]() {
                   player->moveIfPossible(sf::Vector2f(0.f, 1.f));
                   player->setTexture(&gameTextures[objectType::Player][3]);
               }),
        Action(actionKeyword::left,
               [=]() {
                   player->moveIfPossible(sf::Vector2f(-1.f, 0.f));
                   player->setTexture(&gameTextures[objectType::Player][0]);
               }),
        Action(actionKeyword::right,
               [=]() {
                   player->moveIfPossible(sf::Vector2f(1.f, 0.f));
                   player->setTexture(&gameTextures[objectType::Player][0]);
               }),
        Action(actionKeyword::action1,
               [=]() {
                   int switchCount = 0;

                   for (size_t i = 1; i < winFactors.size(); i++) {
                       std::shared_ptr<Switch> s =
                           std::static_pointer_cast<Switch>(winFactors[i]);
                       s->collision(*characters[0]);

                       if (s->isActive()) {
                           switchCount++;
                           s->setTexture(&gameTextures[objectType::Switch][1]);
                       }
                   }
                   if (switchCount == winFactors.size() - 1) {
                       std::shared_ptr<Door> door =
                           std::static_pointer_cast<Door>(winFactors[0]);
                       door->setOpenState(true);
                   }
               }),
        Action(actionKeyword::escape,
               [=]() {
                   currentState = gameState::Menu;
                   loaded = false;
               }),
        Action(actionKeyword::action2,
               [=]() { powerups[BuffType::PlayerSpeed]->buff(2.0); }),
        Action(actionKeyword::action3,
               [=]() { powerups[BuffType::EnemySpeed]->buff(); })

    };

    /*The editorActions contaings all the actions we monitor during the Editor
     * state.*/
    Action editorActions[10] = {
        Action(sf::Keyboard::Num0, [=]() { cellType = objectType::Floor; }),
        Action(sf::Keyboard::Num1, [=]() { cellType = objectType::Wall; }),
        Action(sf::Keyboard::Num2, [=]() { cellType = objectType::Switch; }),
        Action(sf::Keyboard::Num3, [=]() { cellType = objectType::Door; }),
        Action(sf::Keyboard::Num4, [=]() { cellType = objectType::Player; }),
        Action(sf::Keyboard::Num5, [=]() { cellType = objectType::Monster; }),
        Action(sf::Keyboard::Tab, [=]() { draw(EditorUI); }),
        Action(sf::Mouse::Button::Left,
               [&]() {
                   sf::Vector2f mousePos =
                       window.mapPixelToCoords(sf::Mouse::getPosition(window));
                   int index[2] = {int(mousePos.x) / PIXEL16,
                                   int(mousePos.y) / PIXEL16};
                   grid[index[0]][index[1]].setCellType(
                       cellType, &gameTextures[cellType][0]);
               }),
        Action(sf::Mouse::Button::Right,
               [&]() {
                   sf::Vector2f mousePos =
                       window.mapPixelToCoords(sf::Mouse::getPosition(window));
                   int index[2] = {int(mousePos.x) / PIXEL16,
                                   int(mousePos.y) / PIXEL16};
                   grid[index[0]][index[1]].setCellType(
                       objectType::Floor, &gameTextures[objectType::Floor][0]);
               }),
        Action(sf::Keyboard::Escape, [=] {
            int doorCounter = 0;
            int playerCounter = 0;
            int monsterCounter = 0;
            int switchCounter = 0;
            for (auto & row : grid) {
                for (auto & item : row) {
                    if (item.getCellType() == objectType::Door) {
                        doorCounter += 1;
                    } else if (item.getCellType() == objectType::Player) {
                        playerCounter += 1;
                    } else if (item.getCellType() == objectType::Monster) {
                        monsterCounter += 1;
                    } else if (item.getCellType() == objectType::Switch) {
                        switchCounter += 1;
                    }
                }
            }
            if (monsterCounter > 0 && doorCounter > 0 && playerCounter > 0 &&
                switchCounter > 0) {
                factory.writeToFile(grid, "Core/Saves/custom.txt");
                loaded = false;
                currentState = gameState::Menu;
            }
        })};

    ///\brief
    /// Loads the objects from the 'main' vector into their appropriate
    /// sub-vectors.
    ///\details
    /*It will also put them in the right places. i.e. the player will get placed
     * at index 0, monsters after that etc.*/
    void loadSubVectors();

    ///\brief
    /// Loads a tileset.
    ///\details
    /*Used to load a tileset into a container provided the tiles are 16x16
     * pixels.*/
    ///@param file
    /*std::string, the name of the tileset file.*/
    ///@param source
    /*sf::Image &, the source where the image will be put into.*/
    ///@return std::unordered_map<objectType, std::vector<sf::Texture>>
    std::unordered_map<objectType, std::vector<sf::Texture>>
    loadTextures(std::string file, sf::Image & source);

    ///\brief
    /// Draw function for IObjects.
    ///\details
    /*This draw is explicitly for vectors containg shared pointers to
     * IObjects.*/
    ///@param objects
    /*std::vector<std::shared_prt<IObject>> &*/
    void draw(std::vector<std::shared_ptr<IObject>> & objects);

    ///\brief
    /// Draw function for UIElements.
    ///\details
    /*This draw is explicitly for vectors containg shared pointers to
     * UIElements.*/
    ///@param uiElements
    /*std::vector<std::shared_prt<UIElement>> &*/
    void draw(std::vector<std::shared_ptr<UIElement>> & uiElements);

    ///\brief
    /// Draw function for GridCells.
    ///\details
    /*This draw is explicitly for vectors containg shared pointers to
     * GridCells.*/
    ///@param grid
    /*std::vector<std::shared_prt<GridCell>> &*/
    void draw(std::vector<std::vector<GridCell>> & grid);

    ///\brief
    /// Draw function for IObjects
    ///\details
    /*This draw is explicitly for sets containg shared pointers to IObjects.*/
    ///@param grid
    /*std::set<std::shared_ptr<IObject>>& */
    void draw(std::set<std::shared_ptr<IObject>> & objects);

  public:
    Game() {
        windowSize = window.getSize();

        bgSource.loadFromFile("Resources/Textures/background.png");
        loseBgSource.loadFromFile("Resources/Textures/loseBackground.png");
        winBgSource.loadFromFile("Resources/Textures/winBackground.png");

        bgTexture.loadFromImage(
            bgSource,
            sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{windowSize}});
        loseBgTexture.loadFromImage(
            loseBgSource,
            sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{windowSize}});
        winBgTexture.loadFromImage(
            winBgSource,
            sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{windowSize}});

        bgSprite.setTexture(bgTexture);
        loseBgSprite.setTexture(loseBgTexture);
        winBgSprite.setTexture(winBgTexture);
        menuBgSprite.setTexture(winBgTexture);

        gameTextures =
            loadTextures("Resources/Textures/" + textureFile, textureSource);

        std::ifstream file;
        file.open("Core/Saves/menu.txt");
        MenuUI = factory.fileToUi(file);
        file.close();

        file.open("Core/Saves/mapSelection.txt");
        MapSelectionUI = factory.fileToUi(file);
        file.close();

        file.open("Core/Saves/play.txt");
        PlayUI = factory.fileToUi(file);
        file.close();

        file.open("Core/Saves/editor.txt");
        EditorUI = factory.fileToUi(file);
        file.close();

        file.open("Core/Saves/winLose.txt");
        winloseUI = factory.fileToUi(file);
        file.close();

        file.open("Core/Saves/tutorial.txt");
        TutorialUI = factory.fileToUi(file);
        file.close();

        file.open("Core/Saves/store.txt");
        StoreUI = factory.fileToUi(file);
        file.close();

        std::array<int, 3> playerData = factory.readInventoryFromFile();
        points = playerData[0];
        Powerup powerup =
            Powerup({10, 10}, drawables, sf::Color::Yellow, 0,
                    objectType::Powerup, BuffType::PlayerSpeed, playerData[1]);
        Powerup powerup2 =
            Powerup({15, 15}, drawables, sf::Color::Yellow, 0,
                    objectType::Powerup, BuffType::EnemySpeed, playerData[2]);

        powerups[BuffType::PlayerSpeed] = std::make_shared<Powerup>(powerup);
        powerups[BuffType::EnemySpeed] = std::make_shared<Powerup>(powerup2);

        grid = createGrid(window.getSize());
    };

    ///\brief
    /// Creates a matrix of GridCells.
    ///\details
    /*The created grid is based on grid cells of PIXEL16.*/
    ///@param windowSize
    /*sf::Vector2u, windowSize containing the size of the sf::RenderWindow window.*/
    ///@return std::vector<std::vector<GridCell>>
    std::vector<std::vector<GridCell>> createGrid(sf::Vector2u windowSize);

    ///\brief
    /// Finds the index in the grid.
    ///\details
    /*This function find the index in the grid based on a sf::Vector2f position.
    The grid is based on PIXEL16.*/
    ///@param position
    /*sf::Vector2f, the position of which you want the index in the grid.*/
    ///@return std;:array<int,2>
    std::array<int, 2> findIndexInGrid(sf::Vector2f position);

    ///\brief
    /// Algorithm used by the Monster.
    ///\details
    /*This Algorithm finds the next step/direction to go to. He does so by
    checking the value in all the GridCells next to the Monster, comparing which
    one is the fastest and then returning a vector which holds the direction the
    monster should go to. See the details for reversedBFSPathAlgorithm for
    further details on this subject.*/
    ///@return sf::Vector2f, containing the direction the Monster should move to.
    sf::Vector2f findShortestStep();

    ///\brief
    /// Reversed Breath First Search Algorithm.
    ///\details
    /*This Algorithm is an implementation of the BFS algorithm. And can only be
    used for this game. It basically finds the shortest path from the player to
    the Monster (hence "reversed") so the Monster can then use the
    findShortestStep() algorithm to see which direction is the fastest to the
    player. The algorithm iterates over all cells in the grid and checks which
    cells are walkable and which ones aren't. It simultaneously checks on which
    cell the player is and saves that. It then checks all walkable cells from
    the player to the monster using a queue and fills each cell with the
    distance from the player to that respective cell (the value). The algorithm
    does so until it finds the cell containing the monster and then ends. From
    that moment forward, all cells from the monster to the player contain a
    number. The monster can then use the findShortestStep() algorithm to check
    which cells around him have to lowest value, and thus which cell contains
    the shortest path to the player. */
    void reversedBFSPathAlgorithm();

    ///\brief
    /// Function to "light up" the environment.
    ///\details
    /*This Function uses rays to detect its surroundings. It works as follows:
    it creates a line from the center of the player outwards under x degrees. It
    then checks all the GridCells surrounding the player for collision with the
    line. If a GridCell intersects with a line and certain conditions (for
    instance) is it a wall?) apply to the GridCell, the GridCell will be added
    to a vector. The line then rotates 5 degrees, and does this again untill the
    lines made a full circle around the player. We then have a vector containing 
    objects that need to be drawn. */
    ///@return std::vector<std::shared_ptr<IObject>>
    std::vector<std::shared_ptr<IObject>> lantern();

    ///\brief
    /// Runs the game
    ///\details
    /*The game is build using a statemachine to determine what should happen.*/
    void run();
};

#endif