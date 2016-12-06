#pragma once
#include <SFML/Graphics.hpp>

class Stage;
class GameState
{
  static GameState * pInstance;

  GameState() {}
  GameState(const GameState& rs) {
    pInstance = rs.pInstance;
  }

  GameState& operator = (const GameState& rs) {
    if (this != &rs) {
       pInstance = rs.pInstance;
    }

    return *this;
  }

  ~GameState () {}

public:
  sf::RenderWindow *window;
  sf::Clock *deltaClock;
  sf::Clock *gameClock;
  long *frameCount;
  static constexpr float maxFPS = 60.f;

  Stage *currentStage;

  void setup(sf::RenderWindow *_window, sf::Clock *_deltaClock,
             sf::Clock *_gameClock) {
    window = _window;
    deltaClock = _deltaClock;
    gameClock = _gameClock;
    window->setFramerateLimit(maxFPS);
  }

  void setStage(Stage *level) {
    currentStage = level;
  }

  static GameState& getInstance()
  {
    static GameState theInstance;
    pInstance = &theInstance;

    return *pInstance;
  }

  void demo() { std::cout << "other singleton # next - your code ..." << std::endl; }
};

GameState * GameState::pInstance = nullptr;

//
// Global helper macros.
//

#define GS GameState::getInstance()
#define GSInit(width, height, default_title)  \
    sf::RenderWindow window(sf::VideoMode(width, height), default_title); \
    sf::Clock deltaClock; \
    sf::Clock gameClock; \
    GSSetup((&window, &deltaClock, &gameClock));
#define GSSetup(ARGS) GS.setup ARGS
#define GSSetCurrentStage(level) GS.setStage(level)
#define GSGetCurrentStage GS.currentStage
#define GSGetTime GS.gameClock->getElapsedTime()
#define GSGetDeltaTime GS.deltaClock->getElapsedTime()
#define GSGetWindow GS.window
#define GSGetWindowSize GS.window->getSize()
#define GSGetMaxFPS GS.maxFPS
